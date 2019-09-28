#!/usr/bin/env python3
#
# package.py
#
# Simple manifest-based archiver
#
# Author: Sreepathi Pai
#
import argparse
import json
import os
import glob
import sys
import zipfile
import platform

TYPE_PRIMARY = "primary"
TYPE_SECONDARY = "secondary"
VALID_TYPES = set([TYPE_PRIMARY, TYPE_SECONDARY])

SET_IN = "in"
SET_OUT = "out"

class Manifest(object):
    def __init__(self, mf):
        self.path = os.path.dirname(mf)
        self.mf = mf
        self.mt = "primary" # other is secondary
        self.name = None
        self.files = {}

        self.manifest = self.read()

    def set_manifest_type(self, mt):
        assert mt in VALID_TYPES
        self.mt = mt

    def get_manifest_type(self):
        return self.mt

    def add_file(self, s, f):
        if s not in self.files:
            self.files[s] = set()

        self.files[s].add(f)

    def remove_file(self, s, f):
        self.files[s].remove(f)

    def get_files(self, s):
        if s not in self.files:
            return []

        return self.files[s]

    def get_sets(self):
        return self.files.keys()

    def read(self):
        self.mt = TYPE_PRIMARY
        self.files = {}

        with open(self.mf, "rb") as f:
            data = f.read().decode('utf-8')
            if len(data) == 0:
                data = "{}"
                return

        j = json.loads(data)

        if j['version'] == 1:
            self.set_manifest_type(j['type'])
            for s in j['sets']:
                for f in j['sets'][s]:
                    self.add_file(s, f)

            if 'name' in j:
                self.name = j['name']
        else:
            print("ERROR: Don't know how to read manifest version: {j['version']}", file=sys.stderr)

    def write(self):
        out = {'type': self.get_manifest_type(), 'version': 1, 'sets': {}}

        if self.name is not None:
            out['name'] = self.name

        for s in self.get_sets():
            out['sets'][s] = list(self.get_files(s))

        with open(self.mf, "w") as f:
            f.write(json.dumps(out))

    def __str__(self):
        out = []
        for s in sorted(self.get_sets()):
            out.append(f"    {s}:\n\t" + "\n\t".join([x for x in self.get_files(s)]))

        set_files = "\n\n".join(out)
        n = self.name if self.name else "no-name"

        return f"{self.mf}: {self.get_manifest_type()} [{n}]\n{set_files}"

def get_manifests():
    return glob.glob("**/MANIFEST.json", recursive = True)

def package(manifests, sets, output):
    files = []
    name = None

    for m in manifests:
        # pick a name from the first primary MANIFEST
        if not name and m.name and m.mt == TYPE_PRIMARY:
            name = m.name

        for s in sets:
            sf = m.get_files(s)
            if len(sf): files.extend([os.path.join(m.path, f) for f in sf])

    if len(files) == 0:
        print(f"ERROR: No files from set(s) '{','.join(sets)}' found to package.")
        return 0

    if output is None:
        if name is not None:
            output = name + ".zip"
        else:
            print("ERROR: No name found in manifest, and output not specified. Please use -o to specify output archive name", file=sys.stderr)
            return 0

    if os.path.exists(output):
        x = input(f"{output} already exists, overwrite (y/n)? ")
        if x == "y" or x == "Y":
            os.unlink(output)
        else:
            print(f"ERROR: {output} already exists, not overwriting", file=sys.stderr)
            return 0

    try:
        print(f"Creating {output}")
        with zipfile.ZipFile(output, 'x') as z:
            for f in files:
                print(f"\tadding {f}")
                z.write(f, arcname=os.path.join(name, f))

            if 'in' in sets:
                print(f"\tadding {__file__}")
                z.write(__file__, arcname=os.path.join(name, 'package.py'))

                for m in manifests:
                    print(f"\tadding {m.mf}")
                    z.write(m.mf, arcname=os.path.join(name, m.mf))

            if 'out' in sets:
                desc = f"created by package\nplatform: {sys.platform}\nnode: {platform.node()}"
                z.writestr(os.path.join(name, 'PACKAGER-INFO.txt'), desc)

        print("DONE.")
    except Exception as e:
        print(f"ERROR: {e}")
        return 0

    return 1

if __name__ == "__main__":
    p = argparse.ArgumentParser(description="Package files for assignment submission")
    p.add_argument("package_set", nargs="*", help="Sets to package", default = [])
    p.add_argument("-o", dest="output", help="Name of output file")

    args = p.parse_args()

    if len(args.package_set) == 0:
        args.package_set = ['out']

    if not os.path.exists('MANIFEST.json'):
        print(f"ERROR: No MANIFEST.json found in current directory.")
        sys.exit(1)

    m = []
    for f in get_manifests():
        m.append(Manifest(f))
        print("Found and read:", f)

    sys.exit(package(m, args.package_set, args.output))

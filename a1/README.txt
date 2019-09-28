# Assignment 1

## Preliminaries

This assignment must be done alone. You may discuss questions and
potential solutions with your classmates, but you may not look at
their code or their solutions. If in doubt, ask the instructor.

We assume you will use the CSUG machines. You can use other machines,
but we will assume your assignment runs correctly on the CSUG
machines. Always test on the CSUG machines before submitting.

This assignment has two major parts: Parity and Multibyte. You should
attempt Parity first. Instructions for each assignment are in the
comments of the files `parity/parity.c` and `mbstr/mbstr.c`.

## Unpacking this assignment

The command to unpack a zip file on Linux, is:

    unzip a1.zip

This will unpack the contents a1.zip on a Linux system. You should see
a directory `a1`. Go into the directory.


## Read the README file

The command to view a README.txt file in a terminal is:

    less README.txt

Press `q` to quit.

## Smoke tests

### Parity assignment

Go to the `parity` directory:

    cd parity

Then, run `make`.

    make

You should see a file `parity` produced.

Run `parity`:

```
./parity

count_bits test #1: FAIL
count_bits test #2: FAIL
count_bits test #3: FAIL
even_parity test #1: FAIL
even_parity test #2: FAIL
odd_parity test #1: FAIL
odd_parity test #2: FAIL
hamming_distance test: FAIL
```

If you see this, everything is set up properly and now you can edit
the file `parity.c` and solve the assignment.


### Multibyte string assignment

Go to the `mbstr` directory:

    cd mbstr

Then, run `make`.

    make

You should see a file `mbstr` produced.

Run `mbstr`:

```
./mbstr inputs/cat-emojis.txt
```

You should see output:

```
1: 46 bytes, 0 characters
2: 1 bytes, 0 characters
encoding 0x41, expecting nbytes 1, got -1
	got 0x70 expected 0x41
	encoding 0x41: FAIL
encoding 0x80, expecting nbytes 2, got -1
	got 0x70 expected 0xc2
	got 0x43 expected 0x80
	encoding 0x80: FAIL
encoding 0x800, expecting nbytes 3, got -1
	got 0x70 expected 0xe0
	got 0x43 expected 0xa0
	got 0xf3 expected 0x80
	encoding 0x800: FAIL
encoding 0x10000, expecting nbytes 4, got -1
	got 0x70 expected 0xf0
	got 0x43 expected 0x90
	got 0xf3 expected 0x80
	got 0xbf expected 0x80
	encoding 0x10000: FAIL
encoding 114112, expecting nbytes 0, got -1
	encoding 114112: FAIL
decoding { 0x41, 0x42, 0x43, 0x44 }, got value: 0xffffffff, expected 0x400041: FAIL
decoding { 0xc2, 0x80, 0x43, 0x44 }, got value: 0xffffffff, expected 0x800080: FAIL
decoding { 0xf8, 0x41, 0x43, 0x44 }, got value: 0xffffffff, expected 0x0: FAIL
decoding { 0xc1, 0xc0, 0x41, 0x42 }, got value: 0xffffffff, expected 0x0: FAIL
decoding { 0xc0, 0x41, 0x41, 0x42 }, got value: 0xffffffff, expected 0x0: FAIL
decoding { 0xc0, 0x80, 0x41, 0x42 }, got value: 0xffffffff, expected 0x0: FAIL
decoding { 0xe0, 0xa0, 0x80, 0x42 }, got value: 0xffffffff, expected 0xc00800: FAIL
```

Now you can edit the file `mbstr.c` and solve the assignment. See the
`README.txt` in `mbstr` for the correct answers for the other inputs provided.


## Submitting this assignment

To submit this assignment, type:

    ./package.py

You will see output like this:

```
Found and read: MANIFEST.json
Found and read: mbstr/MANIFEST.json
Found and read: parity/MANIFEST.json
Creating a1.zip
	adding mbstr/mbstr.c
	adding parity/parity.c
DONE.
```

This will produce a file called `a1.zip`. Submit this file to the
autograder. Instructions for submission to the Autograder will be
posted on Blackboard after Thursday (an announcement will be sent).

Start early!

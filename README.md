# CS205 2017 Spring Final Projecs --  Remote Attestation and Software Stack Verification based on Trusted Platform Module (TPM)

## Group Member:  
Ronny Ko  
Taosha Wang

## Background

A software stack is the software launch history from the initial booting until "now". The software stack's signature can be represented as a recursive cryptographic hash of the binary files as input values. Every computational step of the software stack signature gets over-written into the TPM chip's same PCR register.   

We cannot arbitrarily modify the PCR register's value, because it is physically outside our CPU.
Thus, software attacks cannot tamper with TPM and its PCR, due to this hardware protection setting. 

So if a malicious software runs before or after the authorized program, its binary will get accumulated into TPM's PCR register,
and the final software stack's signature will become a different value than what we expect. 
This way, we know that some unauthorized program was/is running on our computer.

## Problem Definition

Suppose we cannot run a task manager because our task manager got compromised by the malicious program. 
So the only way for us to investigate the identity of the malicious program is by looking at the TPM chip's PCR register value. Given a list of all known malicious program's binaries and our expected software stack signature, 
we reverse-engineer (i.e. re-compute the recursive SHA1 in a brute-force way for all possibilities) and determine: 

which malicious program(s) were/are running on our compromised computer?
## Parallel Computing

The larger our software stack's size is (i.e. the more programs we have launched), the longer it'll take to brute-force and determine the malicious program's identity. 
And the larger the number of candidate malicious programs is, the longer it'll take to brute-force and determine the malicious program's identity. 

- As the software stack size increases linearly, our the search space grows exponentially.  
- As the number of candidate malicious programs linearly, our search space grows linearly. 

We can use Odyssey to test and determine the feasible maximum size of the software stacks and the feasible number of malicious programs. 
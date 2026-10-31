# file-integrity-monitor

## what is it?
a low-level file integrity monitor that checks if files have been tampered through checkSums

## what does it do? 
It computes SHA-256 checksums for every monitored file then stores the files location, checksum, and last-checked timestamp onto a local SQLite database. 

## Features
* SQlite handling
* SHA-256 checksum 
* File absolute path locating

## Requirements
- OpenSSL
- SQLite3
- CMake 3.14+

## Roadmap 
- Comparative logic to detect changes
- Alerting upon detected tempering
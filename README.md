# Welcome to PDSA!

Mac / Linux CLI  tool for digital file signing and digital signature validation of files signed by this tool.

  
## Table of Contents

*  [Install](https://github.com/paz-lavi/Prefy/PDSA/master/README.md#install)
*  [Create Keys pair](https://github.com/paz-lavi/PDSA/blob/master/README.md#create-keys-pair)
*  [Sign File](https://github.com/paz-lavi/PDSA/blob/master/README.md#sign-file)
*  [Validate Signed File](https://github.com/paz-lavi/Prefy/blob/master/README.md#validate-signed-file)
*  [Validate Key And File](https://github.com/paz-lavi/PDSA/blob/master/README.md#validate-key-and-file)
*  [License](https://github.com/paz-lavi/PDSA/blob/master/README.md#license)

## Install 

* Download the the [install script](https://www.dropbox.com/s/7c71p2e0xy46i6f/install.sh?dl=1)
* Add execute permisions to the file:
```bash
	chmod +x install.sh ## for Mac
	chmod +x install    ## for Linux
```

*  Install the CLI tool 
```bash
	sudo ./install.sh ## for Mac
	sudo ./install    ## for Linux
```

## Create Keys pair
Create pair of key (private and public) to sign files.
```bash
	pdsa keys-generator [-e private key][-d public key] [-b bits size]
```
* [-e private key] optional - Private key file. Default `ras.private` 
* [-d public key] optional - Public key file . Default `ras.public` 
* [-b bits size] optional - Key bits size. Default 64 bits (support in 16,32,64)

## Sign File
Digitally sign files with the keys you generated using the `keys-generator` command.
```bash
	pdsa sign-file [-f file name / path] [-e private key][-d public key][-s signature output file]
```
* [-f file name / path] **required** -  The file name / path to sign on. Signed file will be saved to the same location as `sign_{FILE NAME}`
* [-e private key] optional - Private key file. Default `ras.private`. 
* [-d public key] optional - Public key file . Default `ras.public` .
* [-s signature output file] optional - File to save the digital signature. Default `signature.enc`.

## Validate Signed File
Check if a signed file is valid or not. If the signed file is not valid then it probably modified! 
```bash
	pdsa validate-signed-file [-f file name]
```
* [-f file name / path] **required** -  The signed file name / path to for validate. 

## Validate Key And File
check if public key and signature are match to file (not a signed file - the original one!)
```bash
	pdsa validate-key-and-file [-f file name][-d public key][-s signature file]
```
* [-f file name / path] **required** -  The original file name / path to that signed. 
* [-d public key] optional - Public key file . Default `ras.public` 
* [-s signature file] optional - File that contains  the digital signature. Default `signature.enc`.


## License

```

Copyright 2021 Paz Lavi

Licensed under the Apache License, Version 2.0 (the "License");

you may not use this file except in compliance with the License.

You may obtain a copy of the License at

https://github.com/paz-lavi/PDSA/blob/master/LICENSE

Unless required by applicable law or agreed to in writing, software

distributed under the License is distributed on an "AS IS" BASIS,

WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

See the License for the specific language governing permissions and

limitations under the License.

```
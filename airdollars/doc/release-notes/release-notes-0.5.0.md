AirDollars version 0.5.0 is now available for download at:
http://sourceforge.net/projects/airdollars/files/AirDollars/airdollars-0.5.0/

The major change for this release is a completely new graphical interface that uses the Qt user interface toolkit.

This release include German, Spanish, Spanish-Castilian, Norwegian and Dutch translations. More translations are welcome; join the project at Transifex if you can help:
https://www.transifex.net/projects/p/airdollars/

Please report bugs using the issue tracker at github:
https://github.com/airdollars/airdollars/issues

For Ubuntu users, there is a new ppa maintained by Matt Corallo which you can add to your system so that it will automatically keep airdollars up-to-date.  Just type "sudo apt-add-repository ppa:airdollars/airdollars" in your terminal, then install the airdollars-qt package.

MAJOR BUG FIX  (CVE-2011-4447)

The wallet encryption feature introduced in AirDollars version 0.4.0 did not sufficiently secure the private keys. An attacker who
managed to get a copy of your encrypted wallet.dat file might be able to recover some or all of the unencrypted keys and steal the
associated coins.

If you have a previously encrypted wallet.dat, the first time you run airdollars-qt or airdollarsd the wallet will be rewritten, AirDollars will
shut down, and you will be prompted to restart it to run with the new, properly encrypted file.

If you had a previously encrypted wallet.dat that might have been copied or stolen (for example, you backed it up to a public
location) you should send all of your airdollarss to yourself using a new airdollars address and stop using any previously generated addresses.

Wallets encrypted with this version of AirDollars are written properly.

Technical note: the encrypted wallet's 'keypool' will be regenerated the first time you request a new airdollars address; to be certain that the
new private keys are properly backed up you should:

1. Run AirDollars and let it rewrite the wallet.dat file

2. Run it again, then ask it for a new airdollars address.
AirDollars-Qt: Address Book, then New Address...
airdollarsd: run the 'walletpassphrase' RPC command to unlock the wallet,  then run the 'getnewaddress' RPC command.

3. If your encrypted wallet.dat may have been copied or stolen, send  all of your airdollarss to the new airdollars address.

4. Shut down AirDollars, then backup the wallet.dat file.
IMPORTANT: be sure to request a new airdollars address before backing up, so that the 'keypool' is regenerated and backed up.

"Security in depth" is always a good idea, so choosing a secure location for the backup and/or encrypting the backup before uploading it is recommended. And as in previous releases, if your machine is infected by malware there are several ways an attacker might steal your airdollarss.

Thanks to Alan Reiner (etotheipi) for finding and reporting this bug.

MAJOR GUI CHANGES

"Splash" graphics at startup that show address/wallet/blockchain loading progress.

"Synchronizing with network" progress bar to show block-chain download progress.

Icons at the bottom of the window that show how well connected you are to the network, with tooltips to display details.

Drag and drop support for airdollars: URIs on web pages.

Export transactions as a .csv file.

Many other GUI improvements, large and small.

RPC CHANGES

getmemorypool : new RPC command, provides everything needed to construct a block with a custom generation transaction and submit a solution

listsinceblock : new RPC command, list transactions since given block

signmessage/verifymessage : new RPC commands to sign a message with one of your private keys or verify that a message signed by the private key associated with a airdollars address.

GENERAL CHANGES

Faster initial block download.

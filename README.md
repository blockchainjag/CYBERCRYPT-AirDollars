## Overview

The following repositories has been invaluable to this project:

- https://github.com/JBaczuk/blockchain_fundamentals
- https://github.com/JBaczuk/bitcoin/tree/0.11
- https://github.com/JBaczuk/blockchain-dev-tools
- https://github.com/JBaczuk/cpp_miner
- https://github.com/JBaczuk/secp256k1

I had multiple issues building the QT GUI of newer Bitcoin version and settled on v0.11.3. I aimed for:

- 1 minute blocks
- same 50 coin initial reward
- block halving every 210000 blocks
- retarget difficulty every hour

## Changes

​The following changes have been made to Bitcoin v0.11.3 (as per JBaczuk's guide):

- Renamed the coin
- Change address prefixes
- Message prefix bytes
- RPC and P2P ports
- Seeds
- Block rewards
- Subsidy halving interval
- Block time

I built the following QT GUI nodes:
- Main seed node
  - does not have seeds listed
  - does not mine
- Normal node w/mining
  - will connect to seed node
  - will mine with 1x CPU core
- Normal node w/o mining
  - will connect to seed node
  - will not mine

### `/src/consensus/consensus.h`

Needed to be able to spend coinbase after 5 confirmations; much faster than BTC.
```
line 14: static const int COINBASE_MATURITY = 5; 
```

### `/src/chainparamsbase.cpp`

Changed port numbers.
```
line 20: nRPCPort = 2332; //mainnet
line 33: nRPCPort = 12332; //testnet
```

### `src/rpcmining.cpp`

Commented out to allow 51% attack demonstration. Needed to allow mining on disconnected node.
```
lines 436: //if (vNodes.empty())
lines 437: //    throw JSONRPCError(RPC_CLIENT_NOT_CONNECTED, "AirDollars is not connected!");
```

### `src/qt/optionsmodel.cpp`

Added URL for transaction display:
```
line 65: settings.setValue("strThirdPartyTxUrls", "https://airdollars.codespot.co.za/transaction.php?txid=%s");
line 66:     strThirdPartyTxUrls = settings.value("strThirdPartyTxUrls", "https://airdollars.codespot.co.za/transaction.php?txid=%s").toString();
```

### `src/init.cpp`

To enable/disable CPU mining be default. Use `("-gen", true)` to enable mining.
```
line 1443: GenerateAirDollarss(GetBoolArg("-gen", false), pwalletMain, GetArg("-genproclimit", 1));

```

### `src/chainparams.cpp`

```
consensus.nSubsidyHalvingInterval = 210000; //reward halving every 210000 blocks
consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); //for a lower starting mining difficulty
consensus.nPowTargetTimespan = 1 * 60 * 60; //adjust difficulty every hour
consensus.nPowTargetSpacing = 1 * 60; //1 minute block time
vSeeds.push_back(CDNSSeedData("https://github.com/SeekoeiD/airdollars", "seed.airdollars.codespot.co.za")); //to add 
```

`TotalIssuance.java` will calculate the total runtime and coin issuance:
```
blocks=6930000 //13 years
total=2.0999999996870756E7 //21M
```

## Better CPU mining

pooler-cpuminer v2.4.4 is compatible for solo mining (https://github.com/pooler/cpuminer/releases/tag/v2.4.4).

```
minerd.exe -o http://192.168.100.10:2332 -u user -p pass -a sha256d -R 2 --coinbase-addr=19wD5H2GzviUPZJsZ6bkd4jh6sn6SPXFtn --quiet -t 4
```

You need a `airdollars.conf` file with the following in your data directory to allow access for the mining software:
```
server=1
rest=1
rpcallowip=0.0.0.0/0
rpcuser=user
rpcpassword=pass
```

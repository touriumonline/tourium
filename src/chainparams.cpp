// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2015-2017 The ALQO developers
// Copyright (c) 2017-2018 The Tourium developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>


using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/*
#include "bignum.h"
void GenerateGenesisBlock(CBlock block)
{
	uint256 hashTarget = CBigNum().SetCompact(block.nBits).getuint256();
    uint256 thash;

    while (true)
    {
    	    thash = HashQuark(BEGIN(block.nVersion), END(block.nNonce));
        if (thash <= hashTarget)
            break;
        if ((block.nNonce & 0xFFF) == 0)
        {
            //printf("nonce %08X: hash = %s (target = %s)\n", block.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
        }
        ++block.nNonce;
        if (block.nNonce == 0)
        {
            //printf("NONCE WRAPPED, incrementing time\n");
            ++block.nTime;
        }
    }

    std::cout << block.ToString() << std::endl;
}
*/

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions

static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of(0, uint256("0x00000417c50ab437bd8d1de6206562a63dfcd107b5d35bf782173e5b4dbc9d4b"))
		 (24, uint256("0x000001299c41294fffdd5369491822a8ba95ace7b9068430ebd8a40f62d15d78"))
		 (25, uint256("0x0000046d573d0dddc2af3fe0c7c24a2d1bef7eb31733cfc1c80f62bc2ddd7d3f"))
	 (1000, uint256("0x0000000001307d3cbef4ab1fdff216619dc2bac8de70b7e856d3d7ea0a9d0ed9"))
	(1001, uint256("0x6efefcd94a03075349c86895381c5f7aab69ae773b2216c0b7819f57c3f0160f"))
	(1002, uint256("0x3c52ab7bc54f68d8d866e250d982e4e1fb775ef05587d272def1e4b1983d93dc"))
	 (1003, uint256("0x4cf16fb0cfc7c3f1b31acdc923b65b7f8f254c79782b24dcc9b7e8a85f503d70"))
	 	 (1004, uint256("0xc88283d30aaac196d40abf5f865929306024e4e2d0683142fc0e70db88f5aeef"))
		 	 (1014, uint256("0xc332886ecf91260ed0d72806b6cbccb39422841e5c85acbe874b11d0a853ac31"))				 
    (12492, uint256("0xfc3fa3b3c86c30331786fd6aae54c3d4f4be42895230d953ba22fd9c297a9bb1"));
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
	1546202672, // * UNIX timestamp of last checkpoint block
    24088,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
	1544126812,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
	1544126812,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x75;
        pchMessageStart[1] = 0x6F;
        pchMessageStart[2] = 0x63;
        pchMessageStart[3] = 0x96;
        vAlertPubKey = ParseHex("046cb82f89eb0fe9b7df84f0b87356088ff3f3946ddf001214d8d90a701c682a5c1814ea48d763a87c2d98ee47c88948627a874c782d5ceb887283cfe5ab63e264");
        nDefaultPort = 15110;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // Tourium starting difficulty is 1 / 2^12  //20
		        bnProofOfStakeLimit = ~uint256(0) >> 16;
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Tourium: 5 minutes
        nTargetSpacing = 1 * 60;  // Tourium: 1 minute
        nLastPOWBlock = 1000;
        nMaturity = 26;
        nMasternodeCountDrift = 20;
		nMasternodeColleteralLimxDev = 1500; //Params().MasternodeColleteralLimxDev()
        nModifierUpdateBlock = 1; // we use the version 2 for dmd
        nMaxMoneyOut = 25000000 * COIN;

        const char* pszTimestamp = "TOCN start coin";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04dcd46f6f9dcfe7199429825bc43187828ae27ee52a53f77a7ee43b24ccb3c584ec488d59ac7c72e47b9f3d8dc23bfab2d938e75d166cae94454f196c60671307") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1544126812;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 22058447;

        //GenerateGenesisBlock(genesis);
        /*
        CBlock(hash=0000005fb5bc70df5d3f470497fbf5ec34606df0ca5ca6157424a441cfaa9329, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=03c8762ec4b0597a4437f8fafb7046a718f9f1089aabf9b06ba9560d105febfc, nTime=1519010250, nBits=1e00fff0, nNonce=121211724, vtx=1)
          CTransaction(hash=03c8762ec4, ver=1, vin.size=1, vout.size=1, nLockTime=0)
            CTxIn(COutPoint(0000000000000000000000000000000000000000000000000000000000000000, 4294967295), coinbase 04ffff001d01043a466562727561727920313874682c2032303138202d20537769747a65726c616e6420656d6272616365732063727970746f63757272656e63792e)
            CTxOut(nValue=0.00000000, scriptPubKey=040fbf75ea45bf7eb65f9075e8342b)
        */

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000417c50ab437bd8d1de6206562a63dfcd107b5d35bf782173e5b4dbc9d4b"));
        assert(genesis.hashMerkleRoot == uint256("0x29522dbbd8bba6425fa794795ab979ab2abaf4b4c4575a2d36310c6310c38bd8"));
        
        vSeeds.push_back(CDNSSeedData("45.76.19.24", "45.76.19.24"));
        vSeeds.push_back(CDNSSeedData("95.179.193.202", "95.179.193.202"));
        vSeeds.push_back(CDNSSeedData("149.28.214.186", "149.28.214.186"));
        vSeeds.push_back(CDNSSeedData("95.179.213.15", "95.179.213.15"));
        vSeeds.push_back(CDNSSeedData("185.22.233.171", "185.22.233.171"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 66);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 16);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 137);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md 109 	0x8000006d
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x6d).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "043ad14a1f79017f6282936ee55e04f7b17b5026b1ebc38a796b707095d2f938f7bb7d26f6a9641c0c9032ed801fc3e5b615981c5678346e66f33ce7272d425615";
        strDarksendPoolDummyAddress = "AcmpqXViWUXNroqVNYRdKjKrFM6PNa1oTM";
        nStartMasternodePayments = 1523967685; 
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x64;
        pchMessageStart[1] = 0x44;
        pchMessageStart[2] = 0x65;
        pchMessageStart[3] = 0x54;
        vAlertPubKey = ParseHex("04cd605b716114fa9a44bd92ee6930d53b1aa1bba5e28675a9445d1e54743c2dd5f7b4bf00eb61f9c7bc809fc8df9961aac27e89a6c7d7e1409c2329b3acbcaad0");
        nDefaultPort = 20777;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 10; // Tourium: 10 seconds
        nTargetSpacing = 10;  // Tourium: 10 seconds
        nLastPOWBlock = 200;
        nMaturity = 15;
        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 100000000 * COIN;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
       genesis.nTime = 1544126813;
        genesis.nNonce = 20631470;

        //GenerateGenesisBlock(genesis);
        /*
        CBlock(hash=0000008d766907f5113186ac3e9f198d8d2d96987e6b4a1fc65723050366d94b, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=03c8762ec4b0597a4437f8fafb7046a718f9f1089aabf9b06ba9560d105febfc, nTime=1519010251, nBits=1e00fff0, nNonce=20767169, vtx=1)
          CTransaction(hash=03c8762ec4, ver=1, vin.size=1, vout.size=1, nLockTime=0)
            CTxIn(COutPoint(0000000000000000000000000000000000000000000000000000000000000000, 4294967295), coinbase 04ffff001d01043a466562727561727920313874682c2032303138202d20537769747a65726c616e6420656d6272616365732063727970746f63757272656e63792e)
            CTxOut(nValue=0.00000000, scriptPubKey=040fbf75ea45bf7eb65f9075e8342b)
        */

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000004c1d4882bc7d6a618d762281b2a03270de3a25f1d76455721b440161a57"));

        vFixedSeeds.clear();
        vSeeds.clear();
		
        vSeeds.push_back(CDNSSeedData("testnet.touriumcoin.org", "testnet.touriumcoin.org"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 65);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 18);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 193);
        // Testnet Tourium BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet Tourium BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet Tourium BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "0404fad39689a3ba041f754fde7576f284116a6ad8aab2c3abb9069771c5ee130a793d7ddc8d1dc38ae282720ca71331d77fa82d09d0eca9a6d862fb817ac0fbc7";
        strDarksendPoolDummyAddress = "";
        nStartMasternodePayments = 1519010250;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x14;
        pchMessageStart[1] = 0x54;
        pchMessageStart[2] = 0x95;
        pchMessageStart[3] = 0x64;
        nDefaultPort = 21777;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 5 * 60; // Tourium: 5 minutes
        nTargetSpacing = 1 * 60;  // Tourium: 1 minute
        bnProofOfWorkLimit = ~uint256(0) >> 1;
         genesis.nTime = 1544126814;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 20542301;

        //GenerateGenesisBlock(genesis);
        /*
        CBlock(hash=00000049606f05027a9c1035dbc85f068122b03085c4766389fb69e71508f23e, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=03c8762ec4b0597a4437f8fafb7046a718f9f1089aabf9b06ba9560d105febfc, nTime=1519010252, nBits=1e00fff0, nNonce=14592436, vtx=1)
          CTransaction(hash=03c8762ec4, ver=1, vin.size=1, vout.size=1, nLockTime=0)
            CTxIn(COutPoint(0000000000000000000000000000000000000000000000000000000000000000, 4294967295), coinbase 04ffff001d01043a466562727561727920313874682c2032303138202d20537769747a65726c616e6420656d6272616365732063727970746f63757272656e63792e)
            CTxOut(nValue=0.00000000, scriptPubKey=040fbf75ea45bf7eb65f9075e8342b)
        */

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x6109d084e2c44a63611050576038d272b11985077443b02629e8a7d584820151"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 21777;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}

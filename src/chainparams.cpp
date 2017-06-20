// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
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

/**
 * Main network
 */

static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

static Checkpoints::MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (    0, uint256("0x3fd3991934a8e6b098c644f1900990d397617ae984e01304466e630d10edbf23"))
        (  144, uint256("0x60e5112370e728508b619cb6f9b8f6a4a76b31f0ef44cc1e52ddbd923eca4848"))
        (  270, uint256("0x122c538f4d8abb003557e4d625b27e9f4df11ac1ad230ef422c07ce241fdbd36"))
        ;
static const Checkpoints::CCheckpointData data = {
        &mapCheckpoints,
        1497684047, // * UNIX timestamp of last checkpoint block
        272,          // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        500.0     // * estimated number of transactions per day after checkpoint
    };

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
        ( 0, uint256("0x64e292c3dd873c262c4b906aa4498612bbd266dbf1eeb8e85a0ff3e5280951f9"))
        ;
static const Checkpoints::CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        1497371401,
        0,
        576
    };

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
        boost::assign::map_list_of
        ( 0, uint256("9e6786f11d68dc6275f7f3983ac90209990e1c3a7076f536a3c051e1ec03aebb"))
        ;
static const Checkpoints::CCheckpointData dataRegtest = {
        &mapCheckpointsRegtest,
        0,
        0,
        0
    };

class CMainParams : public CChainParams {
public:
    CMainParams() {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        pchMessageStart[0] = 0x34;
        pchMessageStart[1] = 0x32;
        pchMessageStart[2] = 0x38;
        pchMessageStart[3] = 0x0a;
        vAlertPubKey = ParseHex("040184710fa689ad5023690c80f3a49c8f13f8d45b8c857fbcbc8bc4a8e4d3eb4b10f4d4604fa08dce601aaf0f470216fe1b51850b4acf21b179c45070ac7b03a9");
        nDefaultPort = 1511;
        bnProofOfWorkLimit = ~uint256(0) >> 20;
        nSubsidyHalvingInterval = 300000;
        nEnforceBlockUpgradeMajority = 800;
        nRejectBlockOutdatedMajority = 1200;
        nToCheckBlockUpgradeMajority = 1500;
        nMinerThreads = 0;
        nTargetTimespan = 20 * 60; // 1 days
        nTargetSpacing = 10 * 60; // 10 minutes

        const char* pszTimestamp = "The Real Madrid footballer faces a lawsuit for allegedly defrauding Spain of millions";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 70 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("042f8c498befa678ffe0e39e1522ddcd2cf42e4dca6da248069f958607d0144b042a2ba73d3237bf7a8bf086bd9c1d13443982bf4c05c5c53c2d845077614c750e") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1497371400;
        genesis.nBits    = 0x1e0ffff0;
        genesis.nNonce   = 725264;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x3fd3991934a8e6b098c644f1900990d397617ae984e01304466e630d10edbf23"));
        assert(genesis.hashMerkleRoot == uint256("0xc8cd804eab7a2c8261d04c74bd40b2365c38ad263e61a5a539b03b0be3f04d0c"));
        vSeeds.push_back(CDNSSeedData("mfhcoin.info", "dnsseed.mfhcoin.info"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(48);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(5);
        base58Prefixes[SECRET_KEY] =     list_of(176);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x61)(0x78)(0x32)(0x38);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x61)(0x78)(0x37)(0x61);

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        nEnforceV2AfterHeight = 710000;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x61;
        pchMessageStart[1] = 0x73;
        pchMessageStart[2] = 0x79;
        pchMessageStart[3] = 0x61;
        vAlertPubKey = ParseHex("0466fa7fda80c4df8e7a73c1ca0348e6257dce677f6d73c87117aa8add0c25ac69751e303e1165b37b2ea6ad696b050b9e3e5b86142449e11cb388e7a32bfc276b");
        nDefaultPort = 11511;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 24 * 60 * 60; // 5 days
        nTargetSpacing = 10 * 60; // 10 minutes
        genesis.nTime = 1497371401;
        genesis.nNonce = 2825339;
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x64e292c3dd873c262c4b906aa4498612bbd266dbf1eeb8e85a0ff3e5280951f9"));

        vFixedSeeds.clear();
        vSeeds.clear();
        //vSeeds.push_back(CDNSSeedData("mfhcointools.com", "testnet-seed.mfhcointools.com"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(111);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(196);
        base58Prefixes[SECRET_KEY]     = list_of(239);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x61)(0x78)(0x52)(0x61);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x61)(0x78)(0x33)(0x44);

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;
        nEnforceV2AfterHeight = 400000;
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
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x72;
        pchMessageStart[1] = 0x33;
        pchMessageStart[2] = 0x32;
        pchMessageStart[3] = 0x66;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 1 * 24 * 60 * 60; // 5 days
        nTargetSpacing = 10 * 60; // 10 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1497371402;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 2;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 11411;
        assert(hashGenesisBlock == uint256("0x9e6786f11d68dc6275f7f3983ac90209990e1c3a7076f536a3c051e1ec03aebb"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        // Mfhcoin: v2 enforced using Bitcoin's supermajority rule
        nEnforceV2AfterHeight = -1;
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
class CUnitTestParams : public CMainParams, public CModifiableParams {
public:
    CUnitTestParams() {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 11532;

        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;

        // Mfhcoin: v2 enforced using Bitcoin's supermajority rule
        nEnforceV2AfterHeight = -1;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval)  { nSubsidyHalvingInterval=anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority)  { nEnforceBlockUpgradeMajority=anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority)  { nRejectBlockOutdatedMajority=anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority)  { nToCheckBlockUpgradeMajority=anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks)  { fDefaultConsistencyChecks=afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) {  fAllowMinDifficultyBlocks=afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams *pCurrentParams = 0;

CModifiableParams *ModifiableParams()
{
   assert(pCurrentParams);
   assert(pCurrentParams==&unitTestParams);
   return (CModifiableParams*)&unitTestParams;
}

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams &Params(CBaseChainParams::Network network) {
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

void SelectParams(CBaseChainParams::Network network) {
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

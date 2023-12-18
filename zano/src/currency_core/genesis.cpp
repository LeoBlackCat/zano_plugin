// Copyright (c) 2014-2018 Zano Project
// Copyright (c) 2014-2018 The Louisdor Project
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "genesis.h"

namespace currency
{
#ifndef TESTNET
  const genesis_tx_raw_data ggenesis_tx_raw = { {
      0xa080801a00000101,0x800326b0b4a0f2fd,0xeebe5a6d44a03ed5,0x0e146a5322076dcf,0x992269ec1e34796e,0x003b14d1fe6c757e,0xb0b4a0f2fda08080,0xfd92adf982e70326,0xd8d4b6458b60e1a4,0xa69adb9475e808ed,0x4c383fcedfb6e20a,0xf2fda08080003458,0x8b177f0326b0b4a0,0xef9769ed70d152cd,0x04097d0daa65d123,0x9cd9f8e708f25bbc,0x8080005dfb23beac,0x0326b0b4a0f2fda0,0x6752077f8e75fc8a,0x437f68e0bf774836,0x5a38b52ff21c01c0,0x2d3727ec82ce1425,0xb4f89aecdce08000,0xa07d9fe35f0326b0,0x6c742533eb3b4261,0xfc2ed631332e5e16,0x3d025449393e538b,0x93dc80800015e433,0x70a20307d0ffc2e0,0xb81808dc5029bd46,0x04129413283e31f1,0x143e631cc81020b0,0x80008519d1377ae3,0x05c6c5bc97b1a080,0xf71887a841a72a03,0x681b659b8d2832d4,0x5677f9b15d11d1e6,0xffb2ad80c02a341c,0xbc97b1a08080003f,0xf9cebe7c0305c6c5,0xee223954dc682820,0x8194d2bac0dff6d6,0x86d8a55a30e30183,0xa08080006775f5f0,0x220305c6c5bc97b1,0x3c36e1ebdcee584a,0x4e9ed1a89532ef46,0xf0cb8b411bf6d579,0x00d0e6392ada64d4,0xc6c5bc97b1a08080,0x2fc2b05779450305,0xc9cf47618cc5283e,0xa9e088224807a77e,0xda854e29d2f49646,0x97b1a08080002e74,0xed35180305c6c5bc,0xa78d5545117b8293,0x5c3f8babc16e7062,0xef9324ecd7f86e39,0x808000231900ee9c,0x0305c6c5bc97b1a0,0x0c5bfd9450e89e30,0x194b86e8316970bc,0x5dd8c2e3c2af6ff1,0x4d2ba46f683df89c,0xc5bc97b1a0808000,0xc7cc22ad390305c6,0x891b500cb0799642,0xf5884473a7c01f07,0xeb88d74972d8e36f,0x91ed808000b5d239,0x535a0302fddecd95,0x791c7275cd15d685,0xc2536511d4132e01,0x0c9ad1ee9196aa77,0x80002d55a4efc7d3,0x018e8df2b7f0a080,0x0848b53f974a6a03,0x96b2572cb6015b7d,0xa71b18d2755de52c,0x075e4ca4bd0e4487,0xef93bf82808000ca,0xe23077bc730308f0,0x266a622b7bd9de26,0x4b80410b36c32203,0xb3026d0a2610916c,0xfe8480800084746d,0x6f34b90311e1dea6,0xeb38aee70a8febba,0x8b45df519f0df12e,0x258f0a71e83385da,0x8080000b85701a76,0xdf0308f0ef93bf82,0xb3170ab580f881a3,0x07f0a33f0756a3f4,0xf0721645b2b2bd7b,0x00b0077e03f43a85,0x08f0ef93bf828080,0xf91c1f6308c00f03,0x901a68f4adcc918b,0xad0346f5b7869662,0xd3ed49961fccd915,0xafeaa69a808000f0,0x2c99a01fe90301e3,0xd28642bcae6728d9,0xa6f38c4c630c2b6c,0x2c8a361de6b9294f,0xa69a8080002191e8,0xe134670301e3afea,0x6cf0798aeae985c8,0x4c9b90e1ff211b81,0xc32a954ce05a738b,0x8080009fd2412c6f,0x790301e3afeaa69a,0xb3b0062d6c27a6bb,0x12e133832172b705,0xf3f7d1dfdf336fb8,0x00922d0a879c6027,0x03c6dfd4ccb48080,0x7aa13f278feecf03,0x464f78f86a3e4553,0xa5a464e65c4cf651,0x18f07e7ed8bdd351,0xef93bf82808000dd,0x70b4e3ebae0308f0,0x74c452ecdce312d9,0xca3fb591982461fc,0x3e01aaf9b53ede69,0xfe84808000a4fa65,0x20e5ba0311e1dea6,0xb3e07ec0aabd06a5,0x7bf14a03bf83ccfd,0x6024154f95fd3220,0x808000c13077fa8b,0x5c580316deb183e9,0xc2c948248ab422c3,0xebd3db36bad27d52,0x5fe30392c1525a4e,0x1e00952287d66a6d,0x163df474d5ba8816,0x86f8892015449a71,0x22c93333d9ecb472,0x64fa5516bddfebb3,0x3234373061401303,0x3934353331623633,0x3063626435643130,0x6334636130633932,0x3831383439633530,0x3330336634336332,0x3963306232336630,0x3261623765656133,0x80c9170015633537,0x4c17fba117829117,0x17624a17d2f21711,0xfec81731f9178ced,0x9c17624117a36017,0x1786df17edda1708,0x9ffa17d6e1171b42,0x8b17aa69177ff417,0x179815170a83170c,0xc7e8171ce317da27 },
      { 0x17,0x86,0xd6,0x0e,0x0a,0x00,0x00 } };
#else
  const genesis_tx_raw_data ggenesis_tx_raw = {{
      0xd880800500000101,0x0301f2ee9fa8ff8a,0xac88983c159856b0,0x6334c7d1b567f262,0x284f7f961a7b1266,0x8c0c68c45bab62fc,0xe1dea6fe84808000,0x337be98b45240311,0xab6cd1e4c66e5a33,0x70e889d98e70fd57,0xb97de43fb09861d4,0xf9f0cde08000d574,0x0270187703048dba,0xcac58027c0851473,0xaa10d864c4c87b46,0x820d371e2ba469e8,0xfea08000fce35acc,0x357903049598bddf,0x15df9e58bd0002aa,0xc940a97b60484e8d,0xf94f171e77d0b2d9,0x80003602c681487a,0x0304c38fbab1f8e0,0xc2529eba91cf7476,0x0bbee139aab295f9,0xf1cb8c58a828a2ca,0xcac8f5469af83932,0x5c8a1027cc160900,0x50bdcc9348baf32a,0xa7bd03751819d9fd,0xd6acc8dbbb0d9b29,0x3730614013368b02,0x3533316236333234,0x6264356431303934,0x6361306339323063,0x3834396335306334,0x3366343363323831,0x3062323366303330,0x6237656561333963,0x1700156335373261,0xce5017baa917a8f0,0x0a0eefcc17975617},
      {0x00,0x00}};
#endif
}

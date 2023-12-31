// Copyright (c) 2020-2022 Zano Project (https://zano.org/)
// Copyright (c) 2020-2022 sowle (val@zano.org, crypto.sowle@gmail.com)
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#pragma once
#include "L2S.h"

TEST(ml2s, rsum)
{
  // Ref: Rsum(3, 8, [1, 2, 3, 4, 5, 6, 7, 8], { 1: 1, 2 : 2, 3 : 3 }, { 1: 4, 2 : 5 }) == 659
  
  point_t A = scalar_t::random() * c_point_G;
  point_t result;

  bool r = ml2s_rsum(3, std::vector<point_t>{ A, 2 * A, 3 * A, 4 * A, 5 * A, 6 * A, 7 * A, 8 * A },
    std::vector<scalar_t>{ 1, 2, 3 }, std::vector<scalar_t>{ 4, 5 }, result);
  ASSERT_TRUE(r);
  ASSERT_EQ(result, 659 * A);

  return true;
}

TEST(ml2s, hs)
{
  mp::uint512_t L = c_scalar_L.as_boost_mp_type<mp::uint512_t>();
  L *= 15;
  mp::uint256_t c_256_bit_max = ((mp::uint512_t(1) << 256) - 1).convert_to<mp::uint256_t>();
  std::cout << std::hex << c_256_bit_max << ENDL;

  ASSERT_TRUE(L < c_256_bit_max);

  scalar_t L15(L);

  scalar_t k = epee::string_tools::hex_to_pod<scalar_t>("deefd263cbfed62a3711dd133df3ccbd1c4dc4aac21d7405fd667498bf8ebaa1");
  std::cout << k << ENDL;
  std::cout << k.to_string_as_secret_key() << ENDL;
  mp::uint256_t kw = k.as_boost_mp_type<mp::uint256_t>();
  sc_reduce32(k.m_s);
  std::cout << k << ENDL;
  std::cout << k.to_string_as_secret_key() << ENDL;

  std::cout << kw << ENDL;
  kw = kw % c_scalar_L.as_boost_mp_type<mp::uint256_t>();
  std::cout << kw << ENDL;


  for (size_t i = 0; i < 100000; ++i)
  {
    scalar_t x, y;
    crypto::generate_random_bytes(32, y.m_s);
    x = y;
    memset(x.m_s + 20, 0xff, 11);
    sc_reduce32(x.m_s);
    uint64_t lo = *(uint64_t*)(x.m_s + 20);
    uint64_t hi = *(uint64_t*)(x.m_s + 28) & 0xffffff;
    ASSERT_EQ(lo, 0xffffffffffffffff);
    ASSERT_EQ(hi, 0xffffff);
  }


  scalar_t x = 2, p = 250;
  //sc_exp(r.data(), x.data(), p.data());

  x = 0;

  crypto::hash h;
  //scalar_t r;

  sha3(0, 0, &h, sizeof h);
  LOG_PRINT("SHA3() -> " << h, LOG_LEVEL_0);
  LOG_PRINT("SHA3() -> " << (scalar_t&)h, LOG_LEVEL_0);

  h = crypto::cn_fast_hash(0, 0);
  LOG_PRINT("CN() -> " << h, LOG_LEVEL_0);
  LOG_PRINT("CN() -> " << (scalar_t&)h, LOG_LEVEL_0);

  std::string abc("abc");
  sha3(abc.c_str(), abc.size(), &h, sizeof h);
  LOG_PRINT("SHA3(" << abc << ") -> " << h, LOG_LEVEL_0);
  LOG_PRINT("SHA3(" << abc << ") -> " << (scalar_t&)h, LOG_LEVEL_0);

  h = crypto::cn_fast_hash(abc.c_str(), abc.size());
  LOG_PRINT("CN(" << abc << ") -> " << h, LOG_LEVEL_0);
  LOG_PRINT("CN(" << abc << ") -> " << (scalar_t&)h, LOG_LEVEL_0);


  return true;
}

TEST(ml2s, hsc)
{
  hash_helper_t::hs_t hsc;
  hsc.add_point(c_point_G);
  LOG_PRINT_L0("hsc(G) = " << hsc.calc_hash().as_secret_key());

  hsc.add_point(c_point_G);
  hsc.add_scalar(scalar_from_str("0b2900d8eaf9996d2c5345833b280ef93be5c6881dc26f89ecad7a86441cc10e"));
  hsc.add_point(c_point_G);
  LOG_PRINT_L0("hsc(GsG) = " << hsc.calc_hash().as_secret_key());

  return true;
}


TEST(ml2s, py2cpp)
{
  // verify a signature generated by python's reference code

  std::vector<point_t> B_array = { point_from_str("2f1132ca61ab38dff00f2fea3228f24c6c71d58085b80e47e19515cb27e8d047"), point_from_str("5866666666666666666666666666666666666666666666666666666666666666") };
  ml2s_signature sig;
  sig.z = scalar_from_str("0b2900d8eaf9996d2c5345833b280ef93be5c6881dc26f89ecad7a86441cc10e");
  {
    ml2s_signature_element e;
    e.H_array = { point_from_str("de6169b6f9e4e3dcf450c87f5f9cc5954db82fea3a0afccf285ffff0590cc343"), point_from_str("0d09ad5376090d844afde60f7b0ba78e8010987724e76eeb1f73d490e26ef114") };
    e.T = point_from_str("8df512bbe80238bbb5579e41caab69f209c35560f03a7fdde5d1369b059e38f8");
    e.T0 = point_from_str("fb973d514bb0df3f2bb30038dfe50164a9cd48ef6e7b9ac7a253cbc328f214ab");
    e.Z = point_from_str("27b77c99771a4d8198fd5ebcfae71dc063bd2286006fb9f4a72b72dbcf552c30");
    e.Z0 = point_from_str("a6dd57fcfb5d00c9ad866df931732df491fa0dde14ac76a817399fc2e212666d");
    e.r_array = { scalar_from_str("12921a30105714028187e9ecccf2106d04f6e08dbe7d07001fe3e93a1ffa6e04"), scalar_from_str("fbe2fb0ff0481309db53791b77557eab7359d6cf8274d8dac6ad5092075ec009") };
    e.t = scalar_from_str("002fca7de8af4c57b94b4b49ba2792644dddf09baf729fe31be1c265d2df2e0e");
    e.t0 = scalar_from_str("e0c20ec9adbb047d3b26f8073b49e21e700b9bfe6601b6565ec5ec0e83ad230a");
    sig.elements.emplace_back(e);
  }
  {
    ml2s_signature_element e;
    e.H_array = { point_from_str("661f05591cc6e0a42bc94b5f9d45318248051368306bc199d555306598c6330a"), point_from_str("5281aa630ee6e7ef9af5d758fd98fbf72680e8a97e3329827c9ba24577b06aea") };
    e.T = point_from_str("97463bbf9bf49474853e4e68bb927b8aeb53472b33315930583887ee63d0e341");
    e.T0 = point_from_str("e4877f4e8a9dd8a57955a13a66a2ced96f3e7f2a64ff40beef9641ad4eecbf91");
    e.Z = point_from_str("24a64d04e530772d23a3455047b89569fe796d002dc3d40b57f2ab350eddff47");
    e.Z0 = point_from_str("8db841a90faac3c019f42824fac7177505ca9fb51a21ba0fd8d4112ec9dd9e89");
    e.r_array = { scalar_from_str("52038eb19d0eaffe10cc379ce5a739557adccf4a95ccf77c3159c71d2f166b0f"), scalar_from_str("aebb28319c552708ad2495802a3f585780ae1286146d6e5a845e3074607c0a03") };
    e.t = scalar_from_str("285a411ddcf56747fe11f5053ec3bff7617ad3ed9c6f1929874d90d91fb7680a");
    e.t0 = scalar_from_str("44552f3136dbee1b5b63d4a1a9d8799aed54ddd75ed9ebdf6de0a6e032ac7505");
    sig.elements.emplace_back(e);
  }

  scalar_t m = 31337;

  uint8_t err = 0;
  bool r = ml2s_lnk_sig_verif(m, B_array, sig, &err);

  ASSERT_TRUE(r);

  return true;
}

std::string ml2s_sig_to_python(const std::vector<point_t>& B_array, const ml2s_signature& sig, const std::vector<point_t>& I_array)
{
  std::string str;
  if (B_array.empty() || sig.elements.empty())
    return str;

  auto points_array_to_dict = [](const std::vector<point_t>& v) -> std::string
  {
    std::string s;
    size_t idx = 1;
    for (auto& p : v)
      s += epee::string_tools::num_to_string_fast(idx++) + ": ed25519.Point('" + p.to_string() + "'), ";
    if (s.size() > 2)
      s.erase(s.end() - 2, s.end());
    return s;
  };

  auto points_array_to_array = [](const std::vector<point_t>& v) -> std::string
  {
    std::string s;
    for (auto& p : v)
      s += "ed25519.Point('" + p.to_string() + "'), ";
    if (s.size() > 2)
      s.erase(s.end() - 2, s.end());
    return s;
  };

  auto scalars_array_to_dict = [](const std::vector<scalar_t>& v) -> std::string
  {
    std::string s;
    size_t idx = 1;
    for (auto& p : v)
      s += epee::string_tools::num_to_string_fast(idx++) + ": 0x" + p.to_string_as_hex_number() + ", ";
    if (s.size() > 2)
      s.erase(s.end() - 2, s.end());
    return s;
  };

  std::string indent = "    ";

  str += indent + "B_array = [ ";
  for (auto& B : B_array)
    str += std::string("ed25519.Point('") + B.to_string() + "'), ";
  str.erase(str.end() - 2, str.end());
  str += " ]\n";

  str += indent + "signature = (0x" + sig.z.to_string_as_hex_number() + ", [\n";
  for (size_t i = 0; i < sig.elements.size(); ++i)
  {
    const auto& sel = sig.elements[i];
    str += indent + indent + "{\n";
    str += indent + indent + indent + "'H' : { " + points_array_to_dict(sel.H_array) + " },\n";
    str += indent + indent + indent + "'T' : ed25519.Point('" + sel.T.to_string() + "'),\n";
    str += indent + indent + indent + "'T0' : ed25519.Point('" + sel.T0.to_string() + "'),\n";
    str += indent + indent + indent + "'Z' : ed25519.Point('" + sel.Z.to_string() + "'),\n";
    str += indent + indent + indent + "'Z0' : ed25519.Point('" + sel.Z0.to_string() + "'),\n";
    str += indent + indent + indent + "'r' : { " + scalars_array_to_dict(sel.r_array) + " },\n";
    str += indent + indent + indent + "'t' : 0x" + sel.t.to_string_as_hex_number() + ",\n";
    str += indent + indent + indent + "'t0' : 0x" + sel.t0.to_string_as_hex_number() + "\n";
    str += indent + indent + "},\n";
  }
  str.erase(str.end() - 2, str.end());
  str += "\n";
  str += indent + "])\n";
  str += "\n";

  str += indent + "I_reference = [ " + points_array_to_array(I_array) + " ]\n";

  return str;
}

TEST(ml2s, cpp2py)
{
  // Generate a random sig and python code to check it
  scalar_t m;
  m.make_random();
  size_t n = 8;
  size_t N = 1ull << n;
  size_t L = 8;

  // generate a signature

  std::vector<point_t> ring;
  std::vector<scalar_t> secret_keys;
  std::vector<size_t> ring_mapping;
  std::vector<point_t> key_images;
  generate_test_ring_and_sec_keys(N, L, ring, secret_keys, ring_mapping, key_images);

  ml2s_signature sig;
  ASSERT_TRUE(ml2s_lnk_sig_gen(m, ring, secret_keys, ring_mapping, sig));

  ASSERT_TRUE(ml2s_lnk_sig_verif(m, ring, sig, nullptr, &key_images));

  // generate Python code

  std::string str, indent = "    ";
  str += "import ed25519\n";
  str += "import L2S\n";
  str += "\n";
  str += "def check_sig():\n";
  str += ml2s_sig_to_python(ring, sig, key_images);
  str += indent + "m = 0x" + m.to_string_as_hex_number() + "\n";
  str += indent + "result = L2S.mL2SLnkSig_Verif(len(B_array) * 2, B_array, m, signature)\n";
  str += indent + "print(f\"Verif returned : {result}\")\n";
  str += indent + "\n";
  str += indent + "if result != I_reference:\n";
  str += indent + indent + "print(\"ERROR: Key images don't match\")\n";
  str += indent + indent + "return False\n";
  str += indent + "\n";
  str += indent + "return True\n";
  str += "\n";
  str += "if check_sig():\n";
  str += indent + "print(\"Signature verified, key images matched\")\n";

  epee::file_io_utils::save_string_to_file("ml2s_sig_check_test.py", str);

  return true;
}



TEST(ml2s, sig_verif_performance)
{
  // sig inputs
  scalar_t m = 31337;
  size_t n = 8;
  size_t N = 1ull << n;
  size_t L = 8;

  // perf counters
  uint64_t t_sig = 0;
  uint64_t t_verif = 0;
  size_t tests_cnt = 20; 

  LOG_PRINT_L0("N / 2 = " << N / 2 << ", L = " << L);
  for (size_t p = 0; p < tests_cnt; ++p)
  {
    std::vector<point_t> ring;
    std::vector<scalar_t> secret_keys;
    std::vector<size_t> ring_mapping;
    std::vector<point_t> key_images;
    generate_test_ring_and_sec_keys(N, L, ring, secret_keys, ring_mapping, key_images);

    ml2s_signature sig;
    uint8_t err = 0;
    TIME_MEASURE_START(time_sig);
    bool r = ml2s_lnk_sig_gen(m, ring, secret_keys, ring_mapping, sig, &err);
    TIME_MEASURE_FINISH(time_sig);
    t_sig += time_sig;
    ASSERT_TRUE(r);

    err = 0;
    TIME_MEASURE_START(time_verif);
    r = ml2s_lnk_sig_verif(m, ring, sig, &err);
    TIME_MEASURE_FINISH(time_verif);
    t_verif += time_verif;
    ASSERT_TRUE(r);

    LOG_PRINT_L0(" stats over " << p + 1 << " runs:");
    LOG_PRINT_L0("ml2s_lnk_sig_gen    avg: " << std::right << std::setw(8) << std::fixed << std::setprecision(1) << t_sig / double(p + 1) / 1000.0 << " ms");
    LOG_PRINT_L0("ml2s_lnk_sig_verif  avg: " << std::right << std::setw(8) << std::fixed << std::setprecision(1) << t_verif / double(p + 1) / 1000.0 << " ms");
  }

  return true;
}

TEST(ml2s, sig_verif_performance_2)
{
  // sig inputs
  scalar_t m = 31337;
  crypto::hash mh = crypto::cn_fast_hash(&m, sizeof m);
  size_t n = 8;
  size_t N = 1ull << n;
  size_t L = 1;

  // perf counters
  uint64_t t_sig = 0;
  uint64_t t_verif = 0;
  uint64_t t_sig_v2 = 0;
  uint64_t t_verif_v2 = 0;
  uint64_t t_sig_v3 = 0;
  uint64_t t_verif_v3 = 0;
  size_t tests_cnt = 200;

  LOG_PRINT_L0("N / 2 = " << N / 2 << ", L = " << L);
  for (size_t p = 0; p < tests_cnt; ++p)
  {
    std::vector<point_t> ring;
    std::vector<scalar_t> secret_keys;
    std::vector<size_t> ring_mapping;
    std::vector<point_t> key_images;
    generate_test_ring_and_sec_keys(N, L, ring, secret_keys, ring_mapping, key_images);

    ml2s_signature sig;
    uint8_t err = 0;
    TIME_MEASURE_START(time_sig);
    bool r = ml2s_lnk_sig_gen(m, ring, secret_keys, ring_mapping, sig, &err);
    TIME_MEASURE_FINISH(time_sig);
    t_sig += time_sig;
    ASSERT_TRUE(r);

    err = 0;
    TIME_MEASURE_START(time_verif);
    r = ml2s_lnk_sig_verif(m, ring, sig, &err);
    TIME_MEASURE_FINISH(time_verif);
    t_verif += time_verif;
    ASSERT_TRUE(r);

    ///////////////////////////
    // v2
    ml2s_signature_v2 sig_v2;
    err = 0;
    TIME_MEASURE_START(time_sig_v2);
    r = ml2s_lnk_sig_gen_v2(m, ring, secret_keys, ring_mapping, key_images, sig_v2, &err);
    TIME_MEASURE_FINISH(time_sig_v2);
    t_sig_v2 += time_sig_v2;
    ASSERT_TRUE(r);

    err = 0;
    TIME_MEASURE_START(time_verif_v2);
    r = ml2s_lnk_sig_verif_v2(m, ring, key_images, sig_v2, &err);
    TIME_MEASURE_FINISH(time_verif_v2);
    t_verif_v2 += time_verif_v2;
    ASSERT_TRUE(r);

    ///////////////////////////
    // v3
    {
      std::vector<crypto::public_key> ring;
      std::vector<crypto::secret_key> secret_keys;
      std::vector<size_t> ring_mapping;
      std::vector<crypto::key_image> key_images;
      generate_test_ring_and_sec_keys(N, L, ring, secret_keys, ring_mapping, key_images);

      ml2s_signature_v3 sig_v3;
      err = 0;
      TIME_MEASURE_START(time_sig_v3);
      r = ml2s_lnk_sig_gen_v3(mh, ring, secret_keys, ring_mapping, key_images, sig_v3, &err);
      TIME_MEASURE_FINISH(time_sig_v3);
      t_sig_v3 += time_sig_v3;
      ASSERT_TRUE(r);

      err = 0;
      TIME_MEASURE_START(time_verif_v3);
      r = ml2s_lnk_sig_verif_v3(mh, ring, key_images, sig_v3, &err);
      TIME_MEASURE_FINISH(time_verif_v3);
      t_verif_v3 += time_verif_v3;
      ASSERT_TRUE(r);
    }


    LOG_PRINT_L0(" stats over " << p + 1 << " runs:");
    LOG_PRINT_L0("ml2s_lnk_sig_gen       avg: " << std::right << std::setw(8) << std::fixed << std::setprecision(1) << t_sig / double(p + 1) / 1000.0 << " ms");
    LOG_PRINT_L0("ml2s_lnk_sig_gen_v2    avg: " << std::right << std::setw(8) << std::fixed << std::setprecision(1) << t_sig_v2 / double(p + 1) / 1000.0 << " ms");
    LOG_PRINT_L0("ml2s_lnk_sig_gen_v3    avg: " << std::right << std::setw(8) << std::fixed << std::setprecision(1) << t_sig_v3 / double(p + 1) / 1000.0 << " ms");
    LOG_PRINT_L0("ml2s_lnk_sig_verif     avg: " << std::right << std::setw(8) << std::fixed << std::setprecision(1) << t_verif / double(p + 1) / 1000.0 << " ms");
    LOG_PRINT_L0("ml2s_lnk_sig_verif_v2  avg: " << std::right << std::setw(8) << std::fixed << std::setprecision(1) << t_verif_v2 / double(p + 1) / 1000.0 << " ms");
    LOG_PRINT_L0("ml2s_lnk_sig_verif_v3  avg: " << std::right << std::setw(8) << std::fixed << std::setprecision(1) << t_verif_v3 / double(p + 1) / 1000.0 << " ms");
  }

  return true;
}

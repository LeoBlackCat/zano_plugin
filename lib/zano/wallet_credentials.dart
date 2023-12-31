import 'package:cw_zano/zano/wallet_info.dart';

abstract class WalletCredentials {
  WalletCredentials({
    required this.name,
    this.height,
    this.walletInfo,
    this.password});

  final String name;
  final int? height;
  String? password;
  WalletInfo? walletInfo;
}
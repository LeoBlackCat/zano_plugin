enum SecretStoreKey { zanoWalletPassword, pinCodePassword, backupPassword }

const zanoWalletPassword = "ZANO_WALLET_PASSWORD";
const pinCodePassword = "PIN_CODE_PASSWORD";
const backupPassword = "BACKUP_CODE_PASSWORD";

String generateStoreKeyFor({
  required SecretStoreKey key,
  String walletName = "",
}) {
  var _key = "";

  switch (key) {
    case SecretStoreKey.zanoWalletPassword:
      {
        _key = zanoWalletPassword + "_" + walletName.toUpperCase();
      }
      break;

    case SecretStoreKey.pinCodePassword:
      {
        _key = pinCodePassword;
      }
      break;

    case SecretStoreKey.backupPassword:
      {
        _key = backupPassword;
      }
      break;

    default:
      {}
  }

  return _key;
}

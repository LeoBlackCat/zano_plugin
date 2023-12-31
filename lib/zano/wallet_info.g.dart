// GENERATED CODE - DO NOT MODIFY BY HAND

part of 'wallet_info.dart';

// **************************************************************************
// TypeAdapterGenerator
// **************************************************************************

class WalletInfoAdapter extends TypeAdapter<WalletInfo> {
  @override
  final int typeId = 4;

  @override
  WalletInfo read(BinaryReader reader) {
    final numOfFields = reader.readByte();
    final fields = <int, dynamic>{
      for (int i = 0; i < numOfFields; i++) reader.readByte(): reader.read(),
    };
    return WalletInfo(
      fields[0] == null ? '' : fields[0] as String,
      fields[1] == null ? '' : fields[1] as String,
      fields[2] as WalletType,
      fields[3] == null ? false : fields[3] as bool,
      fields[4] == null ? 0 : fields[4] as int,
      fields[5] == null ? 0 : fields[5] as int,
      fields[6] == null ? '' : fields[6] as String,
      fields[7] == null ? '' : fields[7] as String,
      fields[8] == null ? '' : fields[8] as String,
      fields[11] as String?,
      fields[12] as String?,
      fields[13] as bool?,
    )
      ..addresses = (fields[10] as Map?)?.cast<String, String>()
      ..addressInfos = (fields[14] as Map?)?.map((dynamic k, dynamic v) =>
          MapEntry(k as int, (v as List).cast<AddressInfo>()))
      ..usedAddresses = (fields[15] as List?)?.cast<String>();
  }

  @override
  void write(BinaryWriter writer, WalletInfo obj) {
    writer
      ..writeByte(15)
      ..writeByte(0)
      ..write(obj.id)
      ..writeByte(1)
      ..write(obj.name)
      ..writeByte(2)
      ..write(obj.type)
      ..writeByte(3)
      ..write(obj.isRecovery)
      ..writeByte(4)
      ..write(obj.restoreHeight)
      ..writeByte(5)
      ..write(obj.timestamp)
      ..writeByte(6)
      ..write(obj.dirPath)
      ..writeByte(7)
      ..write(obj.path)
      ..writeByte(8)
      ..write(obj.address)
      ..writeByte(10)
      ..write(obj.addresses)
      ..writeByte(11)
      ..write(obj.yatEid)
      ..writeByte(12)
      ..write(obj.yatLastUsedAddressRaw)
      ..writeByte(13)
      ..write(obj.showIntroCakePayCard)
      ..writeByte(14)
      ..write(obj.addressInfos)
      ..writeByte(15)
      ..write(obj.usedAddresses);
  }

  @override
  int get hashCode => typeId.hashCode;

  @override
  bool operator ==(Object other) =>
      identical(this, other) ||
      other is WalletInfoAdapter &&
          runtimeType == other.runtimeType &&
          typeId == other.typeId;
}

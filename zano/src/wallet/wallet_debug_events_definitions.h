// Copyright (c) 2014-2023 Zano Project
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once



//Wallet Debug Events
struct wde_construct_tx_handle_asset_descriptor_operation
{
  currency::asset_descriptor_operation* pado;
};


//Wallet Debug Events
struct wde_construct_tx_handle_asset_descriptor_operation_before_seal
{
  currency::asset_descriptor_operation* pado;
};


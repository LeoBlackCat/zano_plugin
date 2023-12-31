
// Copyright (c) 2006-2013, Andrey N. Sabelnikov, www.sabelnikov.net
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
// * Neither the name of the Andrey N. Sabelnikov nor the
// names of its contributors may be used to endorse or promote products
// derived from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER  BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 

#pragma once
#include "portable_storage_template_helper.h"
#include "net/http_base.h"
#include "net/http_server_handlers_map2.h"
#include "net/http_client.h"

namespace epee
{
  namespace net_utils
  {

    template<class t_response>
    bool get_http_json_t(const std::string& url, t_response& result_struct, unsigned int timeout = 5000, const std::string& method = "GET")
    {
      std::string body;
      if (!http::fetch_url(url, body, method, "", timeout))
      {
        return false;
      }
      return serialization::load_t_from_json(result_struct, body);
    }


    template<class t_request, class t_response, class t_transport>
    bool invoke_http_json_remote_command2(const std::string& url, t_request& out_struct, t_response& result_struct, t_transport& transport, unsigned int timeout = 5000, const std::string& method = "GET")
    {
      std::string req_param;
      if(!serialization::store_t_to_json(out_struct, req_param))
        return false;

      const http::http_response_info* pri = NULL;
      if(!invoke_request(url, transport, timeout, &pri, method, req_param))
      {
        LOG_PRINT_L1("Failed to invoke http request to  " << url);
        return false;
      }

      if(!pri->m_response_code)
      {
        LOG_PRINT_L1("Failed to invoke http request to  " << url << ", internal error (null response ptr)");
        return false;
      }

      if(pri->m_response_code != 200)
      {
        LOG_PRINT_L1("Failed to invoke http request to  " << url << ", wrong response code: " << pri->m_response_code);
        return false;
      }

      return serialization::load_t_from_json(result_struct, pri->m_body);
    }



    template<class t_request, class t_response, class t_transport>
    bool invoke_http_bin_remote_command2(const std::string& url, t_request& out_struct, t_response& result_struct, t_transport& transport, unsigned int timeout = 5000, const std::string& method = "GET")
    {
      std::string req_param;
      if(!serialization::store_t_to_binary(out_struct, req_param))
        return false;

      LOG_PRINT_L3("[HTTP_BIN] ---> " << "[" << &req_param << "][" << method << "][" << url << "] REQUEST BODY BASE64: " << ENDL << epee::string_encoding::base64_encode(req_param));

      const http::http_response_info* pri = NULL;
      if(!invoke_request(url, transport, timeout, &pri, method, req_param))
      {
        LOG_PRINT_L1("Failed to invoke http request to  " << url);
        return false;
      }

      if(!pri->m_response_code)
      {
        LOG_PRINT_L1("Failed to invoke http request to  " << url << ", internal error (null response ptr)");
        return false;
      }

      LOG_PRINT_L3("[HTTP_BIN] <--- " << "[" << &req_param << "][" << method << "][" << url << "] RESPONSE(" << pri->m_response_code << ") BODY BASE64: " << ENDL << epee::string_encoding::base64_encode(pri->m_body));

      if(pri->m_response_code != 200)
      {
        LOG_PRINT_L1("Failed to invoke http request to  " << url << ", wrong response code: " << pri->m_response_code);
        return false;
      }

      return serialization::load_t_from_binary(result_struct, pri->m_body);
    }


    template<class t_request, class t_response, class t_transport>
    bool invoke_http_json_rpc(const std::string& url, const std::string& method_name, const t_request& out_struct, t_response& result_struct, t_transport& transport, epee::json_rpc::error& err, unsigned int timeout = 5000, const std::string& http_method = "GET", const std::string& req_id = "0")
    {
      epee::json_rpc::request<t_request> req_t = AUTO_VAL_INIT(req_t);
      req_t.jsonrpc = "2.0";
      req_t.id = req_id;
      req_t.method = method_name;
      req_t.params = out_struct;
      epee::json_rpc::response<t_response, epee::json_rpc::error> resp_t = AUTO_VAL_INIT(resp_t);
      if (!epee::net_utils::invoke_http_json_remote_command2(url, req_t, resp_t, transport, timeout, http_method))
      {
        return false;
      }
      err = resp_t.error;
      result_struct = resp_t.result;
      return true;
    }

    template<class t_request, class t_response, class t_transport>
    bool invoke_http_json_rpc(const std::string& url, const std::string& method_name, const t_request& out_struct, t_response& result_struct, t_transport& transport, unsigned int timeout = 5000, const std::string& http_method = "GET", const std::string& req_id = "0")
      {
      epee::json_rpc::request<t_request> req_t = AUTO_VAL_INIT(req_t);
      req_t.jsonrpc = "2.0";
      req_t.id = req_id;
      req_t.method = method_name;
      req_t.params = out_struct;
      epee::json_rpc::response<t_response, epee::json_rpc::error> resp_t = AUTO_VAL_INIT(resp_t);
      if(!epee::net_utils::invoke_http_json_remote_command2(url, req_t, resp_t, transport, timeout, http_method))
      {
        return false;
      }
      if(resp_t.error.code || resp_t.error.message.size())
      {
        LOG_PRINT_L0("RPC call of \"" << method_name << "\" returned error: " << resp_t.error.code << ", message: " << resp_t.error.message);
        return false;
      }
      result_struct = resp_t.result;
      return true;
    }

    template<class t_command, class t_transport>
    bool invoke_http_json_rpc(const std::string& url, typename t_command::request& out_struct, typename t_command::response& result_struct, t_transport& transport, unsigned int timeout = 5000, const std::string& http_method = "GET", const std::string& req_id = "0")
    {
      return invoke_http_json_rpc(url, t_command::methodname(), out_struct, result_struct, transport, timeout, http_method, req_id);
    }

  }
}

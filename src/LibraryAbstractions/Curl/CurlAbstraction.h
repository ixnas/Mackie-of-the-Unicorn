//
// Created by Sjoerd Scheffer on 17/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_CURLABSTRACTION_H
#define MACKIE_OF_THE_UNICORN_CURLABSTRACTION_H

#include <string>
#include <map>

namespace MackieOfTheUnicorn::LibraryAbstractions::Curl
{
	/// Abstraction for cURL.
	class CurlAbstraction
	{
	  public:
		virtual ~CurlAbstraction() = default;

		/// Sets the URL to send a request to.
		virtual void SetURL(std::string url) = 0;

		/// Sets a list of request headers.
		virtual void SetHeaders(std::map<std::string, std::string> headers) = 0;

		/// Sets the request body.
		virtual void SetPostData(std::string postData) = 0;

		/// Sends the request.
		virtual void Perform() = 0;

		/// Returns the headers from the response.
		virtual std::string GetResponseHeaders() = 0;

		/// Returns the body from the response.
		virtual std::string GetResponseBody() = 0;

		/// Resets the object while keeping the connection alive.
		virtual void Reset() = 0;

		/// Clears the set request headers.
		virtual void ClearHeaders() = 0;
	};
}
#endif // MACKIE_OF_THE_UNICORN_CURLABSTRACTION_H

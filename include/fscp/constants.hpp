/*
 * libfscp - C++ portable OpenSSL cryptographic wrapper library.
 * Copyright (C) 2010-2011 Julien Kauffmann <julien.kauffmann@freelan.org>
 *
 * This file is part of libfscp.
 *
 * libfscp is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of
 * the License, or (at your option) any later version.
 *
 * libfscp is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * In addition, as a special exception, the copyright holders give
 * permission to link the code of portions of this program with the
 * OpenSSL library under certain conditions as described in each
 * individual source file, and distribute linked combinations
 * including the two.
 * You must obey the GNU General Public License in all respects
 * for all of the code used other than OpenSSL.  If you modify
 * file(s) with this exception, you may extend this exception to your
 * version of the file(s), but you are not obligated to do so.  If you
 * do not wish to do so, delete this exception statement from your
 * version.  If you delete this exception statement from all source
 * files in the program, then also delete it here.
 *
 * If you intend to use libfscp in a commercial software, please
 * contact me : we may arrange this for a small fee or no fee at all,
 * depending on the nature of your project.
 */

/**
 * \file constants.hpp
 * \author Julien Kauffmann <julien.kauffmann@freelan.org>
 * \brief The constants.
 */

#ifndef FSCP_CONSTANTS_HPP
#define FSCP_CONSTANTS_HPP

#include <boost/asio.hpp>

#include <cryptoplus/cipher/cipher_algorithm.hpp>
#include <cryptoplus/x509/certificate.hpp>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/array.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/optional.hpp>
#include <boost/utility/enable_if.hpp>

#include <stdint.h>
#include <vector>
#include <map>

namespace fscp
{
	class enumeration_type
	{
		public:

			typedef uint8_t value_type;

			enumeration_type() : m_value(value_type()) {}
			enumeration_type(value_type _value) : m_value(_value) {}

			value_type value() const { return m_value; }
			operator value_type() const { return m_value; }

		private:

			value_type m_value;
	};

	inline bool operator==(const enumeration_type& lhs, const enumeration_type& rhs)
	{
		return (lhs.value() == rhs.value());
	}

	// This overload is needed to accomodate with the ambiguity raised by the implicit conversion to value_type
	inline bool operator==(const enumeration_type& lhs, const enumeration_type::value_type& rhs)
	{
		return (lhs.value() == rhs);
	}

	// This overload is needed to accomodate with the ambiguity raised by the implicit conversion to value_type
	inline bool operator==(const enumeration_type::value_type& lhs, const enumeration_type& rhs)
	{
		return (lhs == rhs.value());
	}

	inline bool operator!=(const enumeration_type& lhs, const enumeration_type& rhs)
	{
		return (lhs.value() != rhs.value());
	}

	// This overload is needed to accomodate with the ambiguity raised by the implicit conversion to value_type
	inline bool operator!=(const enumeration_type& lhs, const enumeration_type::value_type& rhs)
	{
		return (lhs.value() != rhs);
	}

	// This overload is needed to accomodate with the ambiguity raised by the implicit conversion to value_type
	inline bool operator!=(const enumeration_type::value_type& lhs, const enumeration_type& rhs)
	{
		return (lhs != rhs.value());
	}

	template<typename Type> struct is_enumeration_type : boost::is_base_of<enumeration_type, Type> {};

	template <typename Type>
	inline typename boost::enable_if<is_enumeration_type<Type>, std::ostream&>::type operator<<(std::ostream& os, const Type& value)
	{
		return os << value.to_string();
	}

	template <typename Type>
	inline typename boost::enable_if<is_enumeration_type<Type>, std::istream&>::type operator>>(std::istream& is, Type& value)
	{
		std::string str;

		if (is >> str)
		{
			value = Type::from_string(str);
		}

		return is;
	}

	/**
	 * \brief The session number type.
	 */
	typedef uint32_t session_number_type;

	/**
	 * \brief The challenge type.
	 */
	typedef boost::array<uint8_t, 32> challenge_type;

	/**
	 * \brief The hash type.
	 */
	typedef boost::array<uint8_t, 32> hash_type;

	/**
	 * \brief The hash list type.
	 */
	typedef std::vector<hash_type> hash_list_type;

	/**
	 * \brief The contact map type.
	 */
	typedef std::map<hash_type, boost::asio::ip::udp::endpoint> contact_map_type;

	/**
	 * \brief The sequence number type.
	 */
	typedef uint32_t sequence_number_type;

	/**
	 * \brief The current protocol version.
	 */
	const unsigned char CURRENT_PROTOCOL_VERSION = 2;

	/**
	 * \brief The length of the GCM tag.
	 */
	const size_t GCM_TAG_LENGTH = 16;

	/**
	 * \brief The different message types.
	 */
	enum message_type
	{
		MESSAGE_TYPE_HELLO_REQUEST = 0x00,
		MESSAGE_TYPE_HELLO_RESPONSE = 0x01,
		MESSAGE_TYPE_PRESENTATION = 0x02,
		MESSAGE_TYPE_SESSION_REQUEST = 0x03,
		MESSAGE_TYPE_SESSION = 0x04,
		MESSAGE_TYPE_DATA_0 = 0x70,
		MESSAGE_TYPE_DATA_1 = 0x71,
		MESSAGE_TYPE_DATA_2 = 0x72,
		MESSAGE_TYPE_DATA_3 = 0x73,
		MESSAGE_TYPE_DATA_4 = 0x74,
		MESSAGE_TYPE_DATA_5 = 0x75,
		MESSAGE_TYPE_DATA_6 = 0x76,
		MESSAGE_TYPE_DATA_7 = 0x77,
		MESSAGE_TYPE_DATA_8 = 0x78,
		MESSAGE_TYPE_DATA_9 = 0x79,
		MESSAGE_TYPE_DATA_10 = 0x7A,
		MESSAGE_TYPE_DATA_11 = 0x7B,
		MESSAGE_TYPE_DATA_12 = 0x7C,
		MESSAGE_TYPE_DATA_13 = 0x7D,
		MESSAGE_TYPE_DATA_14 = 0x7E,
		MESSAGE_TYPE_DATA_15 = 0x7F,
		MESSAGE_TYPE_CONTACT_REQUEST = 0xFD,
		MESSAGE_TYPE_CONTACT = 0xFE,
		MESSAGE_TYPE_KEEP_ALIVE = 0xFF
	};

	/**
	 * \brief The different channel numbers.
	 */
	enum channel_number_type
	{
		CHANNEL_NUMBER_0 = 0,
		CHANNEL_NUMBER_1 = 1,
		CHANNEL_NUMBER_2 = 2,
		CHANNEL_NUMBER_3 = 3,
		CHANNEL_NUMBER_4 = 4,
		CHANNEL_NUMBER_5 = 5,
		CHANNEL_NUMBER_6 = 6,
		CHANNEL_NUMBER_7 = 7,
		CHANNEL_NUMBER_8 = 8,
		CHANNEL_NUMBER_9 = 9,
		CHANNEL_NUMBER_10 = 10,
		CHANNEL_NUMBER_11 = 11,
		CHANNEL_NUMBER_12 = 12,
		CHANNEL_NUMBER_13 = 13,
		CHANNEL_NUMBER_14 = 14,
		CHANNEL_NUMBER_15 = 15
	};

	/**
	 * \brief The endpoint type type.
	 */
	enum endpoint_type_type
	{
		ENDPOINT_TYPE_IPV4 = 0x04,
		ENDPOINT_TYPE_IPV6 = 0x06
	};

	/**
	 * \brief The cipher algorithm type.
	 */
	class cipher_algorithm_type : public enumeration_type
	{
		public:

			static const value_type unsupported = 0x00;
			static const value_type aes256_gcm = 0x01;

			cipher_algorithm_type() {}
			cipher_algorithm_type(value_type _value) : enumeration_type(_value) {}

			/**
			 * \brief Check whether the instance is a valid cipher algorithm.
			 * \return true if the cipher algorithm is valid.
			 */
			bool is_valid() const
			{
				switch (value())
				{
					case unsupported:
					case aes256_gcm:
						return true;
				}

				return false;
			}

			/**
			 * \brief Get a string representation of the cipher algorithm.
			 * \return A string representation.
			 */
			std::string to_string() const
			{
				switch (value())
				{
					case unsupported:
						throw std::runtime_error("Unsupported cipher algorithm value: " + boost::lexical_cast<std::string>(static_cast<int>(value())));
					case aes256_gcm:
						return aes256_gcm_string;
				}

				throw std::invalid_argument("Invalid cipher algorithm value: " + boost::lexical_cast<std::string>(static_cast<int>(value())));
			}

			/**
			 * \brief Get a cipher algorithm from its string representation.
			 * \param str The string representation.
			 * \return The cipher algorithm.
			 *
			 * If str does not match any known cipher algorithm
			 */
			static cipher_algorithm_type from_string(const std::string& str)
			{
				if (str == aes256_gcm_string)
				{
					return aes256_gcm;
				}

				throw std::invalid_argument("Invalid cipher algorithm string representation: " + str);
			}

			/**
			 * \brief Get the cipher algorithm associated with the instance:.
			 * \return The associated cipher algorithm.
			 *
			 * If the instance is not supported, a std::runtime_error is thrown.
			 */
			cryptoplus::cipher::cipher_algorithm to_cipher_algorithm() const
			{
				switch (value())
				{
					case unsupported:
						throw std::runtime_error("Unsupported cipher algorithm value: " + boost::lexical_cast<std::string>(static_cast<int>(value())));
					case aes256_gcm:
						return cryptoplus::cipher::cipher_algorithm(NID_aes_256_gcm);
				}

				throw std::invalid_argument("Invalid cipher algorithm value: " + boost::lexical_cast<std::string>(static_cast<int>(value())));
			}

		private:

			static const std::string aes256_gcm_string;
	};

	/**
	 * \brief The cipher algorithm list type.
	 */
	typedef std::vector<cipher_algorithm_type> cipher_algorithm_list_type;

	/**
	 * \brief An algorithm info type.
	 */
	struct algorithm_info_type
	{
		cipher_algorithm_type cipher_algorithm;
	};

	inline std::ostream& operator<<(std::ostream& os, const algorithm_info_type& ai)
	{
		const std::string cipher_algorithm = (ai.cipher_algorithm != cipher_algorithm_type::unsupported) ? boost::lexical_cast<std::string>(ai.cipher_algorithm) : "<unsupported>";

		return os << cipher_algorithm;
	}

	/**
	 * \brief The certificate digest algorithm.
	 */
	const int CERTIFICATE_DIGEST_ALGORITHM = NID_sha256;

	/**
	 * \brief The session keep-alive period.
	 */
	const boost::posix_time::time_duration SESSION_KEEP_ALIVE_PERIOD = boost::posix_time::seconds(10);

	/**
	 * \brief The session timeout.
	 */
	const boost::posix_time::time_duration SESSION_TIMEOUT = SESSION_KEEP_ALIVE_PERIOD * 3;

	/**
	 * \brief Check if a message type is a DATA type message.
	 * \param type The message type.
	 * \return true if the message type is one from MESSAGE_TYPE_DATA_0 to MESSAGE_TYPE_DATA_15.
	 */
	inline bool is_data_message_type(message_type type)
	{
		return (type >= MESSAGE_TYPE_DATA_0) && (type <= MESSAGE_TYPE_DATA_15);
	}

	/**
	 * \brief Convert a DATA message type to a channel number.
	 * \param type The message type. Must be one from MESSAGE_TYPE_DATA_0 to MESSAGE_TYPE_DATA_15.
	 * \return The channel number.
	 */
	channel_number_type to_channel_number(message_type type);

	/**
	 * \brief Convert a channel number to a DATA message type.
	 * \param channel_number The channel number.
	 * \return The DATA message type.
	 */
	message_type to_data_message_type(channel_number_type channel_number);

	/**
	 * \brief Gives a hash for a certificate.
	 * \param buf The output buffer.
	 * \param buflen The output buffer length.
	 * \param cert The certificate.
	 */
	void get_certificate_hash(void* buf, size_t buflen, cryptoplus::x509::certificate cert);

	/**
	 * \brief Gives a hash for a certificate.
	 * \param cert The certificate.
	 */
	hash_type get_certificate_hash(cryptoplus::x509::certificate cert);
}

#endif /* FSCP_CONSTANTS_HPP */

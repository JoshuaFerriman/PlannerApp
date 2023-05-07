#include "User.h"


User::User(std::string username, std::string password, bool salt)
{
	User::username = username;
	User::password = password;

	if (salt = true) {
		User::salt = GenerateSalt();
	}
}

/*
std::string User::SHA256(std::string data)
{
	CryptoPP::byte const* pbData = (CryptoPP::byte*)data.data();
	unsigned int nDataLen = data.size();
	CryptoPP::byte abDigest[CryptoPP::SHA256::DIGESTSIZE];

	CryptoPP::SHA256().CalculateDigest(abDigest, pbData, nDataLen);

	return std::string((char*)abDigest);
}
*/

std::string User::GenerateSalt()
{
	std::string temp;
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(1, 6);
	temp = std::to_string(distribution(generator));
	return temp;
}

bool User::AssertUsernameAndPass(DatabaseAccessor &databaseAccessor)
{
	std::string sqlStatement = 
	{ 
		"SELECT PASSWORD,SALT  from USERS" \
						 
		"WHERE USERNAME = '" + User::username + "'"
	};
	
	databaseAccessor.TableSELECT(sqlStatement.data()); 

	return true;
}

bool User::UserLogin(DatabaseAccessor& databaseAccessor)
{
	bool login = false;

	login = AssertUsernameAndPass(databaseAccessor);

	return login;
}

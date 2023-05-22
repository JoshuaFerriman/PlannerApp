#include "User.h"
#include <iostream>

#define SALT_LENGTH 10

User::User(std::string username, std::string password)
{
	User::username = username;
	User::salt, salt = GenerateSalt();
	User::hashedPassword = SaltAndHashPassword(password);

}

User::User()
{

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

void User::TestGenerateSalt() {
	// Call the private GenerateSalt function
	std::string salt = GenerateSalt();

	// Output the salt to the console
	std::cout << "Generated Salt: " << salt << std::endl;
}

std::string User::GenerateSalt()
{
	static std::default_random_engine generator(std::random_device{}());

	std::uniform_int_distribution<int> distribution(32, 126);

	std::string temp;

	for (int i = 0; i < SALT_LENGTH; i++)
	{
		temp += static_cast<char>(distribution(generator));
	}
	

	return temp;
}

std::string User::SaltAndHashPassword(std::string password)
{
	SHA256 sha256;

	std::string digest = password + User::salt;

	digest = sha256(digest);

	return digest;

}

bool User::AssertUsernameAndPass(DatabaseAccessor &databaseAccessor)
{
	std::string sqlStatement = 
	{ 
		"SELECT PASSWORD,SALT from USERS " \
						 
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

bool User::UserCreate(DatabaseAccessor& databaseAccessor)
{


	return true;
}
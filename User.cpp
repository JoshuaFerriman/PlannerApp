#include "User.h"
#include <iostream>

#define SALT_LENGTH 10

User::User(DatabaseAccessor& databaseAccessor, std::string username, std::string password)
{
	User::username = username;
	User::salt = GenerateSalt();
	// std::cout << salt << "\n";
	User::hashedPassword = SaltAndHashPassword(password, User::salt);
	// std::cout << hashedPassword << "\n";


	UserCreateRecord(databaseAccessor);
}

User::User(std::string username, std::string password)
{
	User::username = username;
	User::salt = GenerateSalt();
	// std::cout << salt << "\n";
	User::hashedPassword = SaltAndHashPassword(password, User::salt);
	// std::cout << hashedPassword << "\n";
}

User::User()
{

}

std::string User::GetUsername()
{
	return User::username;
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

std::string User::SaltAndHashPassword(std::string password, std::string salt)
{
	SHA256 sha256;

	std::string digest = password + salt;

	digest = sha256(digest);

	return digest;

}

bool User::AssertUsernameAndPass(DatabaseAccessor &databaseAccessor)
{

	

	return true;
}

bool User::UserLogin(DatabaseAccessor& databaseAccessor, std::string username, std::string password, User* currentUser)
{
	bool login = false;


	std::string sqlStatement =
	{
		"SELECT * from USERS " \

		"WHERE USERNAME = '" + username + "';"
	};

	std::vector<std::vector<std::string>> userPassAndSalt;
	userPassAndSalt = databaseAccessor.TableSELECTWhere(sqlStatement.data());

	if (userPassAndSalt.size() == 1)
	{
		std::string hashedPW = userPassAndSalt[0][1];
		std::string salt = userPassAndSalt[0][2];
		if (hashedPW == SaltAndHashPassword(password, salt))
		{
			login = true;
			
			currentUser->hashedPassword = hashedPW;
			currentUser->username = userPassAndSalt[0][0];
			currentUser->salt = salt;
		}
	}
	else
	{
		std::cout << "Login failed, username not recognised";
	}





	return login;
}

bool User::UserCreateRecord(DatabaseAccessor& databaseAccessor)
{
	std::vector<std::string> fieldValues = { User::username, User::hashedPassword, User::salt };

	databaseAccessor.TableINSERT(users, fieldValues);

	return true;
}
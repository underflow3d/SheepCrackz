# include <iostream>
# include <fstream>
# include <openssl/md5.h>
# include <openssl/sha.h>
# include <iomanip>
# include <string>
# define newline '\n'
using namespace std;

std::string md5Hash(const std::string& message) {
    unsigned char hash[MD5_DIGEST_LENGTH];
    MD5_CTX md5;
    MD5_Init(&md5);
    MD5_Update(&md5, message.c_str(), message.length());
    MD5_Final(hash, &md5);

    std::stringstream ss;
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }

    return ss.str();
}

std::string sha256Hash(const std::string& data) {
    SHA256_CTX sha256Context;
    SHA256_Init(&sha256Context);
    SHA256_Update(&sha256Context, data.c_str(), data.length());

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_Final(hash, &sha256Context);

    std::string hashString;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        char hex[3];
        sprintf(hex, "%02x", hash[i]);
        hashString += hex;
    }

    return hashString;
}

int main(int argc, char* args[]) {
	if(argc < 4 || argc > 4) {
		cout << "Usage: ./sheepcrackz hash_file wordlist_file hash_type" << newline;
		return 0;
	} else {
		ifstream hash_file(args[1]);
		ifstream wordlist_file(args[2]);
		string type = args[3];
		string hash;
		getline(hash_file, hash);
		if(type == "md5") {
			string word;
			while(getline(wordlist_file, word)) {
				if(md5Hash(word) == hash) {
					cout << "Password Found" << newline;
					cout << hash << ":" << word << newline;
					return 0;
				}
			}
			cout << "Not Found!" << newline;
			return 0;
			
		}
		else if(type == "sha256") {
			string word;
			while(getline(wordlist_file, word)) {
				if(sha256Hash(word) == hash) {
					cout << "Password Found" << newline;
					cout << hash << ":" << word << newline;
					return 0;
				}

			}
			cout << "Not Found!" << newline;
			return 0;
		}
		else {
			cout << "Unsupported Hash Type!" << newline;
			return 0;
		}
	}
	return 0;
}

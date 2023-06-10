# include <iostream>
# include <fstream>
# include <openssl/md5.h>
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
		}
		else {
			cout << "Unsupported Hash Type!" << newline;
			return 0;
		}
	}
	return 0;
}

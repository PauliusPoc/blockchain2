#include <array>
#include <vector>
#include <string>
#include "hash.h"
#include <sstream>

/*
std::array<uint8_t, 32> create_merkle(bc::hash_list& merkle)
{
    // Stop if hash list is empty or contains one element
    if (merkle.empty())
        return bc::null_hash;
    else if (merkle.size() == 1)
        return merkle[0];

    // While there is more than 1 hash in the list, keep looping...
    while (merkle.size() > 1)
    {
        // If number of hashes is odd, duplicate last hash in the list.
        if (merkle.size() % 2 != 0)
            merkle.push_back(merkle.back());
        // List size is now even.
        assert(merkle.size() % 2 == 0);

        // New hash list.
        bc::hash_list new_merkle;
        // Loop through hashes 2 at a time.
        for (auto it = merkle.begin(); it != merkle.end(); it += 2)
        {
            // Join both current hashes together (concatenate).
            bc::data_chunk concat_data(bc::hash_size * 2);
            auto concat = bc::serializer<
                    decltype(concat_data.begin())>(concat_data.begin());
            concat.write_hash(*it);
            concat.write_hash(*(it + 1));
            // Hash both of the hashes.
            bc::hash_digest new_root = bc::bitcoin_hash(concat_data);
            // Add this to the new list.
            new_merkle.push_back(new_root);
        }
        // This is the new list.
        merkle = new_merkle;

        // DEBUG output -------------------------------------
        //        std::cout << "Current merkle hash list:" << std::endl;
        //        for (const auto& hash: merkle)
        //            std::cout << "  " << bc::encode_base16(hash) << std::endl;
        //        std::cout << std::endl;
        // --------------------------------------------------
    }
    // Finally we end up with a single item.
    return merkle[0];
}*/

std::string create_merkle(std::vector<std::string> merkle) {

	if (merkle.empty()) {
		return "";
	}
	if (merkle.size() == 1) {
		return merkle[0];
	}

	while (merkle.size() > 1) {
		if (merkle.size() % 2 == 1) {
			merkle.push_back(merkle.back());
		}
		if (merkle.size() % 2 == 0) terminate;

		std::vector<std::string> nMerkle = std::vector<std::string>{};
		nMerkle.reserve(merkle.size() % 2);
		for (int i = 0; i < merkle.size(); i += 2) {

			std::stringstream strm;
			strm << (merkle[i] + merkle[i + 1]);
			nMerkle.push_back(hash(strm.str()));
		}
		merkle = nMerkle;
	}
	return(merkle[0]);
}
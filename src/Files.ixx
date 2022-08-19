export module Util:Files;

import :NumericalTypes;

import <array>;
import <filesystem>;
import <fstream>;
import <optional>;
import <vector>;

export
{
	template<size_t size>
	std::optional<std::array<u8, size>> ReadFileIntoArray(const auto& path)
	{
		std::ifstream ifs{ path, std::ifstream::in | std::ifstream::binary };
		if (!ifs) {
			return {};
		}
		/* Test the file size */
		ifs.seekg(0, ifs.end);
		if (ifs.tellg() != size) {
			return {};
		}
		/* Read the file */
		std::array<u8, size> arr;
		ifs.seekg(0, ifs.beg);
		ifs.read((char*)arr.data(), size);
		return arr;
	}


	std::optional<std::vector<u8>> ReadFileIntoVector(const auto& path)
	{
		std::ifstream ifs{ path, std::ifstream::in | std::ifstream::binary };
		if (!ifs) {
			return {};
		}

		std::vector<u8> vec;
		ifs.seekg(0, ifs.end);
		size_t size = ifs.tellg();
		vec.resize(size);

		ifs.seekg(0, ifs.beg);
		ifs.read((char*)vec.data(), size);

		return vec;
	}
}
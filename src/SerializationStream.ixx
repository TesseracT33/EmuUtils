export module Util:SerializationStream;

import <array>;
import <deque>;
import <fstream>;
import <queue>;
import <string>;
import <utility>;
import <vector>;


export enum class SerializationMode {
	Read, Write
};


/* Used for save states and configuration files; reads or writes data from/to files */
export class SerializationStream
{
	bool has_error = false; // an error has occured while reading/writing.
	bool is_open = false;
	std::fstream fstream{};
	SerializationMode mode;

	void Stream(void* obj, size_t size)
	{
		if (has_error) {
			return;
		}
		if (mode == SerializationMode::Write) {
			fstream.write((const char*)obj, size);
		}
		else {
			fstream.read((char*)obj, size);
		}
		if (!fstream) {
			has_error = true; // todo; implement better error handling
		}
	}

public:
	SerializationStream(SerializationMode mode) : has_error(false), is_open(false), mode(mode) {}

	SerializationStream(SerializationMode mode, const std::string& file_path) : mode(mode)
	{
		Open(file_path);
	}

	SerializationStream(const SerializationStream& other) = delete;

	SerializationStream(SerializationStream&& other) noexcept
	{
		*this = std::move(other);
	}

	SerializationStream& operator=(const SerializationStream& other) = delete;

	SerializationStream& operator=(SerializationStream&& other) noexcept
	{
		if (this != &other) {
			this->fstream.swap(other.fstream);
			this->is_open = other.is_open;
			this->has_error = other.has_error;
			this->mode = other.mode;
			other.Close();
		}
		return *this;
	}

	bool HasError() const
	{
		return this->has_error;
	}

	void Close()
	{
		if (is_open) {
			fstream.close();
			is_open = false;
		}
		has_error = false;
	}

	void Open(const std::string& file_path)
	{
		auto ios_base = [&] {
			if (mode == SerializationMode::Read) {
				return std::ios::in | std::ios::binary;
			}
			else {
				return std::ios::out | std::ios::binary | std::ios::trunc;
			}
		}();
		if (is_open) {
			fstream.close();
		}
		fstream.open(file_path, ios_base);
		is_open = !!fstream;
		has_error = !fstream;
	}

	template<typename T, size_t size>
	void StreamArray(std::array<T, size>& array)
	{
		Stream(array.data(), sizeof(T) * size);
	}

	/* We cannot take the address of (pointer/ref) of a bitfield.
	So take it by copy, read/write from/to it, and then return it.
	The caller will need to make sure that the result is not discarded. */
	template<typename T>
	[[nodiscard]] T StreamBitfield(T bitfield)
	{
		Stream(&bitfield, sizeof(T));
		return bitfield;
	}

	template<typename T>
	void StreamDeque(std::deque<T>& deque)
	{
		if (mode == SerializationMode::Read) {
			deque.clear();
			size_t size;
			Stream(&size, sizeof(size_t));
			if (size > 0) {
				deque.reserve(size);
			}
			for (size_t i = 0; i < size; i++) {
				T t;
				Stream(&t, sizeof(T));
				deque.push_back(t);
			}
		}
		else {
			size_t size = deque.size();
			Stream(&size, sizeof(size_t));
			for (T& t : deque) {
				Stream(&t, sizeof(T));
			}
		}
	}

	template<typename T>
	void StreamPrimitive(T& primitive)
	{
		Stream(&primitive, sizeof(T));
	}

	template<typename T>
	void StreamQueue(std::queue<T>& queue)
	{
		if (mode == SerializationMode::Read)
		{
			while (!queue.empty()) {
				queue.pop();
			}
			size_t size;
			Stream(&size, sizeof(size_t));
			for (size_t i = 0; i < size; i++) {
				T t;
				Stream(&t, sizeof(T));
				queue.push(t);
			}
		}
		else
		{
			size_t size = queue.size();
			Stream(&size, sizeof(size_t));
			auto tmp_queue = queue;
			while (!tmp_queue.empty()) {
				T t = tmp_queue.front();
				tmp_queue.pop();
				Stream(&t, sizeof(T));
			}
		}
	}

	void StreamString(std::string& str)
	{
		if (mode == SerializationMode::Read) {
			size_t size;
			Stream(&size, sizeof(size_t));
			char* c_str = new char[size + 1]{};
			Stream(c_str, size * sizeof(char));
			str = std::string(c_str);
			delete[] c_str;
		}
		else {
			const char* c_str = str.c_str();
			size_t size = std::strlen(c_str);
			Stream(&size, sizeof(size_t));
			Stream((void*)c_str, size * sizeof(char));
		}
	}

	template<typename T>
	void StreamVector(std::vector<T>& vec)
	{
		if (mode == SerializationMode::Read) {
			vec.clear();
			size_t size = 0;
			Stream(&size, sizeof(size_t));
			if (size > 0) {
				vec.reserve(size);
			}
			for (size_t i = 0; i < size; i++) {
				T t;
				Stream(&t, sizeof(T));
				vec.push_back(t);
			}
		}
		else {
			size_t size = vec.size();
			Stream(&size, sizeof(size_t));
			for (T& t : vec) {
				Stream(&t, sizeof(T));
			}
		}
	}
};
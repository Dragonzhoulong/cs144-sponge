#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity): _capacity(capacity) {}

size_t ByteStream::write(const string &data) {
    size_t can_write = remaining_capacity();
    size_t real_write = min(can_write, data.size());
    for (size_t i = 0; i < real_write; i++) {
        _buffer.push_back(data[i]);
    }
    _written_bytes += real_write;
    return real_write;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    string out = "";
    size_t canPeek = min(len, _buffer.size());
    for (size_t i = 0; i < canPeek; i++) {
        out.push_back(_buffer[i]);
    }
    return out;
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) { 
    if (len > _buffer.size()){
        set_error();
        return;
    }
    for (size_t i = 0; i < len; i++) {
        _buffer.pop_front();
    }
    _read_bytes += len;
 }

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    string out ="";
    if (len > _buffer.size()){
        set_error();
        return out;
    }
    for (size_t i = 0; i < len; i++) {
        out.push_back(_buffer[i]);
        _buffer.pop_front();
    }
    _read_bytes += len;
    return out;
}

void ByteStream::end_input() {_input_endedflag = true;}

bool ByteStream::input_ended() const { return _input_endedflag; }

size_t ByteStream::buffer_size() const { return _buffer.size(); }

bool ByteStream::buffer_empty() const { return _buffer.size()==0; }

bool ByteStream::eof() const { return buffer_empty()&&input_ended(); }

size_t ByteStream::bytes_written() const { return _written_bytes; }

size_t ByteStream::bytes_read() const { return _read_bytes; }

size_t ByteStream::remaining_capacity() const { 
    return _capacity - _buffer.size(); 
    }

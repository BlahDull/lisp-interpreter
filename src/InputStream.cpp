#include "../headers/InputStream.hh"

// Method that will return the next Atom in the stream, and remove the Atom from the stream as well
Atom InputStream::eat() {
    Atom atom = *stream.begin();
    if (!stream.empty()) {
        stream.erase(stream.begin());
    }
    return atom;
}

// Method that will return the next Atom in the stream, without removing it
Atom InputStream::peek() {
    Atom atom = *stream.begin();
    return atom;
}

// Method to push an Atom to the front of the stream
void InputStream::push_front(Atom x) {
    stream.insert(stream.begin(), x);
}

// Method to push an atom to the back of the stream
void InputStream::push_back(Atom x) {
    stream.push_back(x);
}

// Helper method to print out the contents of the stream
void InputStream::print_tokens() {
    cout << "[ ";
    for (Atom atom : stream) {
        if (atom.is_token) {
            if (atom.token_val != NOT_EQUAL)
                cout << atom.token_val << " ";
            else cout << "!=" << " ";
        } else {
            cout << atom.value << " ";
        }
    }
    cout << "]" << endl;
}

// Helper method to check if the stream is empty
bool InputStream::is_empty() {
    return stream.empty();
}
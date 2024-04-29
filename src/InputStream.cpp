#include "../headers/InputStream.hh"

Atom InputStream::eat() {
    Atom atom = *stream.begin();
    if (!stream.empty()) {
        stream.erase(stream.begin());
    }
    return atom;
}
Atom InputStream::peek() {
    Atom atom = *stream.begin();
    return atom;
}
void InputStream::push_front(Atom x) {
    stream.insert(stream.begin(), x);
}
void InputStream::push_back(Atom x) {
    stream.push_back(x);
}
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

bool InputStream::is_empty() {
    return stream.empty();
}
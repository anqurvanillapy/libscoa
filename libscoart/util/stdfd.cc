namespace scoa {
    // TODO: Non-blocking stdio
    void afputs(int fd, std::string str); // int - stdin, stdout, stderr
    
    // Asynchronous character input/output (not stream, just concatenation for
    // invoking afputs).
    template <typename T>
    class astdio {
    public:
        void operator<<(const T&);
    private:
        std::string buf;
    };
} // namespace scoa

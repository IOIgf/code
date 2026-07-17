/*
 * @Author: Milk_Dragon 
 * @Date: 2026-07-17 14:13:02 
 * @Last Modified by: Milk_Dragon
 * @Last Modified time: 2026-07-17 14:37:11
 */
#include<bits/stdc++.h>
#define int long long
#ifndef _IO
#define _IO

#if __cplusplus >= 201402L

namespace IO {

	template <typename T>
	struct is_signed_int {
		static constexpr bool value = is_integral<T>::value && is_signed<T>::value;
	};
	template <typename T>
	struct is_unsigned_int {
		static constexpr bool value = is_integral<T>::value && is_unsigned<T>::value;
	};
#if __SIZEOF_POINTER__ == 8
	using i128 = __int128;
	using u128 = __uint128_t;
	template <>
	struct is_signed_int<i128> {
		static constexpr bool value = true;
	};
	template <>
	struct is_unsigned_int<u128> {
		static constexpr bool value = true;
	};
#endif

	template <size_t S>
	class in_buffer {
		char b[S], *p1 = b;
		const char *p2 = b;
		istream *f;

	public:
		in_buffer(istream *f) : f(f) {}
		char getc() {
			return p1 != p2 || (p2 = b + f->rdbuf()->sgetn(p1 = b, S)) != b ? *(p1++) : EOF;
		}
		istream &raw() {
			return *f;
		}
	};

	template <size_t S>
	class out_buffer {
		char b[S], *p1 = b;
		ostream *f;

	public:
		out_buffer(ostream *f) : f(f) {}
		void putc(const char x) {
			p1 == b + S ? f->rdbuf()->sputn(p1 = b, S), 0 : 0;
			*(p1++) = x;
		}
		~out_buffer() {
			f->rdbuf()->sputn(b, p1 - b), p1 = b;
		}
	};

	template <size_t S>
	class my_istream {
		using is = my_istream;
		in_buffer<S> *const f;
#define skip(f1)                 \
		char c = f->getc();          \
		for (; f1(c); c = f->getc()) \
		if (!~c)                 \
		return;
#define skip2(f1, f2)                \
		char c = f->getc();              \
		for (; f1(c); f2, c = f->getc()) \
		if (!~c)                     \
		return;
		template <typename T>
		void rdu(T &x) const {
			skip(!isdigit);
			for (x = 0; isdigit(c); c = f->getc()) x = x * 10 + (c & 15);
		}
		template <typename T>
		void rds(T &x) const {
			bool m = 0;
			skip2(!isdigit, m |= c == 45);
			for (x = 0; isdigit(c); c = f->getc()) x = x * 10 + (c & 15);
			if (m)
				x = -x;
		}
		void rdc(char &x) const {
			skip(isspace);
			x = c;
		}
		void rdcs(char *s) const {
			skip(isspace);
			for (; ~c && !isspace(c); c = f->getc()) * (s++) = c;
			*s = 0;
		}
		void rdstr(string &s) const {
			skip(isspace);
			s = {};
			for (; ~c && !isspace(c); c = f->getc()) s += c;
		}

	public:
		my_istream(in_buffer<S> *f) : f(f) {}
		char get() const {
			return f->getc();
		}
		template <typename T, enable_if_t<is_unsigned_int<T>::value> * = nullptr>
		friend is operator>>(const is f, T &x) {
			return f.rdu(x), f;
		}
		template <typename T, enable_if_t<is_signed_int<T>::value> * = nullptr>
		friend is operator>>(const is f, T &x) {
			return f.rds(x), f;
		}
		friend is operator>>(const is f, char &x) {
			return f.rdc(x), f;
		}
		friend is operator>>(const is f, char *s) {
			return f.rdcs(s), f;
		}
		friend is operator>>(const is f, string &s) {
			return f.rdstr(s), f;
		}
		is getline(char *s) const {
			char c = f->getc();
			if (!~c)
				return *this;
			for (; ~c && c != 10 && c != 13; f->getc()) *(s++) = c;
			*s = 0;
			return *this;
		}
		is getline(string &s) const {
			char c = f->getc();
			if (!~c)
				return *this;
			s = {};
			for (; ~c && c != 10 && c != 13; c = f->getc()) s += c;
			return *this;
		}
#undef skip
	};

	template <size_t S>
	class my_ostream {
		using os = my_ostream;
		out_buffer<S> *const f;
		template <class T>
		void pr(const T x) const {
			if (x > 9)
				pr(x / 10);
			f->putc((x % 10) | 48);
		}

	public:
		my_ostream(out_buffer<S> *f) : f(f) {}
		os put(const char c) const {
			return f->putc(c), *this;
		}
		template <typename T, enable_if_t<is_unsigned_int<T>::value> * = nullptr>
		friend os operator<<(const os f, const T x) {
			return f.pr(x), f;
		}
		template <typename T, enable_if_t<is_signed_int<T>::value> * = nullptr>
		friend os operator<<(const os f, const T x) {
			return x < 0 ? f.f->putc(45), f.pr(-x) : f.pr(x), f;
		}
		friend os operator<<(const os f, const char x) {
			return f.f->putc(x), f;
		}
		friend os operator<<(const os f, const char *s) {
			for (; *s;) f.f->putc(*(s++));
			return f;
		}
		friend os operator<<(const os f, const string &s) {
			for (auto x : s) f.f->putc(x);
			return f;
		}
	};

}  // namespace IO

#define with_buffer
#ifdef with_buffer
namespace IO {
	static constexpr size_t IS = 1 << 16, OS = 1 << 16;
	in_buffer<IS> stdin_buf(&cin);
	my_istream<IS> my_cin(&stdin_buf);
	out_buffer<OS> stdout_buf(&cout);
	my_ostream<OS> my_cout(&stdout_buf);
	int _SYNC_WITH_STDIO_0 = (cin.tie(0)->sync_with_stdio(0), 0);
}
using IO::my_cin;
using IO::my_cout;
#define cin my_cin
#define cout my_cout
#endif  // with_buffer
#endif  // __cplusplus>=201402L
#endif  // _IO
int n,q,t;
bool f;
int a[700005],b[700005];
int l,r,op;
int gcd(int a,int b){
    if(b==0)return a;
    return gcd(b,a%b);
}
signed main(){
    cin>>t;
    while(t--){
        cin>>n>>q;
        for(int i=1;i<=n;i++)cin>>a[i];
        for(int i=1;i<=n;i++)cin>>b[i];
        for(int i=1;i<=q;i++){
            cin>>op>>l>>r;
            if(op==1){
                for(int j=l;j<=r;j++)a[j]+=b[j];
            }
            else{
                if(l==r){
                    cout<<a[l]<<'\n';
                    continue;
                }
                int gc=gcd(a[l],a[l+1]);
                for(int j=l+2;j<=r;j++){
                    gc=gcd(gc,a[j]);
                }
                cout<<gc<<'\n';
            }
        }
    }
    return 0;
}
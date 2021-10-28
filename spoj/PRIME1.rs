use std::cmp::*;
use std::io;
use std::io::prelude::*;

fn int() -> usize {
    let mut r = 0usize;
    loop {
        let mut buf = [0u8; 1];
        io::stdin().read_exact(&mut buf);
        if !('0' as u8 <= buf[0] && buf[0] <= '9' as u8) { break; }
        r = r * 10 + (buf[0] - '0' as u8) as usize;
    }
    return r;
}

fn main() {
    let t = int();

    // filter the primes less than 40000
    let mut is_prime_base = [true; 40000];
    for i in 2..40000 {
        let mut x = i * i;
        while x < 40000 {
            is_prime_base[x] = false;
            x += i;
        }
    }

    // loop for multiple test cases
    for _ in 0..t {
        let m = int();
        let n = int();
        let mut is_prime_large = [true; 100001];
        for i in 2..40000 {
            if is_prime_base[i] {
                let mut x = max((m - 1) / i * i + i, i * i);
                while x <= n {
                    is_prime_large[x - m] = false;
                    x += i;
                }
            }
        }

        // 1 isn't a prime
        if m == 1 { is_prime_large[0] = false; }

        // output
        for i in m..=n {
            if is_prime_large[i - m] {
                println!("{}", i);
            }
        }
        println!();
    }
}

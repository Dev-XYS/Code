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

fn line() -> String {
    let mut buf = String::new();
    io::stdin().read_line(&mut buf);
    buf.pop();
    return buf;
}

fn main() {
    let t = int();
    for _ in 0..t {
        let n = int();
        let mut accounts = vec![String::new(); n];
        for i in 0..n {
            accounts[i] = line();
        }
        line();
        accounts.sort();
        let mut c = 1;
        for i in 0..n {
            if i == n - 1 || accounts[i] != accounts[i + 1] {
                println!("{}{}", accounts[i], c);
                c = 1;
            }
            else { c += 1; }
        }
        println!();
    }
}

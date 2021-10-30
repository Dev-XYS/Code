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

fn rev(mut x: usize) -> usize {
    let mut r = 0;
    while x > 0 {
        r = r * 10 + x % 10;
        x /= 10;
    }
    return r;
}

fn main() {
    let t = int();
    for _ in 0..t {
        let x = int();
        let y = int();
        println!("{}", rev(rev(x) + rev(y)));
    }
}

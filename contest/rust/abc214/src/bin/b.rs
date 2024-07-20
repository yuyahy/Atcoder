#[allow(unused_imports)]
use itertools::{iproduct, Itertools};
#[allow(unused_imports)]
use num_traits::pow;
#[allow(unused_imports)]
use proconio::{
    fastout, input,
    marker::{Chars, Usize1},
};
#[allow(unused_imports)]
use std::cmp::{max, min};
#[allow(unused_imports)]
use std::collections::{HashMap, HashSet, VecDeque};
#[allow(unused_imports)]
use std::iter::FromIterator;
#[allow(non_snake_case)]
#[fastout]
fn main() {
    input! {
        S: i64, T: i64,
    }
    // 考察メモ

    let mut cnt = 0;

    for a in 0..=10000 {
        for b in 0..=10000 {
            let c = S - (a + b);
            if c < 0 {
                continue;
            }
            for c_ in 0..=c {
                if a * b * c_ <= T {
                    // println!("a={}, b={}, c={}", a, b, c);
                    cnt += 1;
                }
            }
        }
    }
    println!("{}", cnt);
}

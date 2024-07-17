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
        A: usize, B: usize,
    }
    // 考察メモ

    match (A, B) {
        (a, b) if a > 0 && b == 0 => println!("Gold"),
        (a, b) if a == 0 && b > 0 => println!("Silver"),
        _ => println!("Alloy"),
    }
}

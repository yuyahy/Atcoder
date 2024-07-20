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
        N: usize,
    }
    // 考察メモ

    let range1 = 1..=125;
    let range2 = 126..=211;
    let range3 = 212..=214;

    match N {
        x if range1.contains(&x) => println!("4"),
        x if range2.contains(&x) => println!("6"),
        x if range3.contains(&x) => println!("8"),
        _ => panic!(""),
    }
}

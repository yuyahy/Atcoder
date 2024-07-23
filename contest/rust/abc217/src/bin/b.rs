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
    // input! {
    //     S1: String,
    //     S2: String,
    //     S3: String,
    // }
    // 考察メモ

    let mut contests = HashSet::new();
    contests.insert("ABC");
    contests.insert("ARC");
    contests.insert("AGC");
    contests.insert("AHC");

    for i in 0..3 {
        input! {
            S: String,
        }
        contests.remove(S.as_str());
    }
    println!("{}", contests.iter().next().unwrap());
}

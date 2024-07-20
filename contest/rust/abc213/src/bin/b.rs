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
        mut A: [usize; N],
    }
    // 考察メモ

    let A_bkup = A.clone();

    A.sort_by(|a, b| b.cmp(a));

    match A_bkup.iter().position(|&x| x == A[1]) {
        Some(index) => println!("{}", index + 1),
        None => println!("error"),
    }
}

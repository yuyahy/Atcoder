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
        S: Chars,
    }
    // 考察メモ
    let S: String = S.iter().collect();
    let mut target_index = 0;
    match S.find('1') {
        Some(index) => {target_index=index;},
        None => println!("The character '1' was not found in the string."),
    }
    if target_index % 2 == 0 {
        println!("Takahashi");
    } else {
        println!("Aoki");
    }
}

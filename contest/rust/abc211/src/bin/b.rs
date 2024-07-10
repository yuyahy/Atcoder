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
        S1:Chars,
        S2:Chars,
        S3:Chars,
        S4:Chars,
    }

    let mut set = HashSet::new();
    set.insert(S1);
    set.insert(S2);
    set.insert(S3);
    set.insert(S4);

    if set.len() == 4 {
        println!("Yes");
    } else {
        println!("No");
    }
}

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
        // S: [String; N], T: [String; N],
    }
    // 考察メモ

    let mut S: Vec<String> = Vec::new();
    let mut T: Vec<String> = Vec::new();

    for _ in 0..N {
        input! {
            s: String, t: String,
        }
        S.push(s);
        T.push(t);
    }

    for i in 0..N - 1 {
        let name = format!("{} {}", S[i], T[i]);
        for j in i + 1..N {
            let name_other = format!("{} {}", S[j], T[j]);
            if name == name_other {
                println!("Yes");
                return;
            }
        }
    }
    println!("No");
}

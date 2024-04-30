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

#[fastout]
fn main() {
    input! {
        N: usize,
        mut st: [(String, usize); N],
    }
    // 高さで昇順ソート
    st.sort_by_key(|&(_, num)| num);
    // 2番目に高い山の名称を取得
    let (result, _) = &st[st.len() - 2];
    println!("{}", result);
}

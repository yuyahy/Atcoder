if [ "$#" -ne 2 ]; then
    echo "エラー: 引数が正しく指定されていません。2つの引数が必要です。"
    exit 0  # エラーコード1で終了する
fi

# コンテスト名称
CONTEST_NAME=$1
# 精進する問題の番号(e.g. 'A','B',...etc)
PROBLEM_NUM=$2

atcoder-tools gen --workspace /workspaces/atcoder/contest --template /workspaces/atcoder/my_template.cpp $1
cd /workspaces/atcoder/contest/$1/

# 精進する問題以外を全て削除する
for dir in */; do
    dir=${dir%/}  # 末尾のスラッシュを取り除く
    if [[ -d "$dir" && "$dir" != "$PROBLEM_NUM" ]]; then
        echo "Remove: $dir"
        rm -rf "$dir"
    fi
done

# Note: source {シェルスクリプト名}で実行する必要がある
cd /workspaces/atcoder/contest/$1/$2
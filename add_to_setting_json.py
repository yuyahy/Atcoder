import argparse
import subprocess
import json

def add_to_setting_json(contest_name: str):
    # JSONファイルのパスを指定
    file_path = "/workspaces/atcoder/.vscode/settings.json"
    new_project_path = f"/workspaces/atcoder/contest/rust/{contest_name}/Cargo.toml"

    # JSONファイルを読み込む
    with open(file_path, 'r') as file:
        data = json.load(file)

    # "rust-analyzer.linkedProjects" 配列に新しいプロジェクトパスを追加
    if "rust-analyzer.linkedProjects" in data:
        data["rust-analyzer.linkedProjects"].append(new_project_path)
    else:
        data["rust-analyzer.linkedProjects"] = [new_project_path]

    # 変更をJSONファイルに書き戻す
    with open(file_path, 'w') as file:
        json.dump(data, file, indent=4)

    print(f"Added {new_project_path} to rust-analyzer.linkedProjects")

def retrieve_contest_files(contest_name: str):
    #result = subprocess.run(['cargo compete new', f"{contest_name}"], capture_output=True, text=True)
    result = subprocess.run(['cargo', "compete", "new", f"{contest_name}"], capture_output=True, text=True)
    # 結果を表示
    print(result.stdout)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='取得するコンテスト名')
    parser.add_argument('contest', type=str)

    args = parser.parse_args()
    # コンテストファイルの取得
    retrieve_contest_files(args.contest)
    # rust-analyzerのためにsetting.jsonへ追加
    add_to_setting_json(args.contest)


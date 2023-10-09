python -m pip install markupsafe==2.0.1
# agenlogin tessoku-book --workspace /workspaces/atcoder
echo 'asub="atcoder-tools submit -f -u"'
# TODO コンパイルオプションを増やす or makefileにする
#echo 'alias atest="g++ -Wfatal-errors --std=c++17 -I /tmp/ac-library main.cpp -D DEFINED_ONLY_IN_LOCAL; atcoder-tools test"' >> /root/.bashrc
echo 'alias atest="g++-12  -Wfatal-errors -Wall -Wextra -Wshadow -Wconversion -Wfloat-equal -std=gnu++20 -I /tmp/ac-library main.cpp -D DEFINED_ONLY_IN_LOCAL; atcoder-tools test"' >> /root/.bashrc
echo 'alias agen="atcoder-tools gen --without-login --workspace=/workspaces/atcoder --template /workspaces/atcoder/my_template.cpp"' >> /root/.bashrc
echo 'alias agenlogin="atcoder-tools gen --workspace /workspaces/atcoder --template /workspaces/atcoder/my_template.cpp"' >> /root/.bashrc
echo 'alias asub="atcoder-tools submit -u"' >> /root/.bashrc

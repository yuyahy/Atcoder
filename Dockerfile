FROM python:3.8

RUN apt-get update \
    && apt-get -y install --no-install-recommends apt-utils dialog 2>&1 \
    && apt-get -y install git iproute2 procps lsb-release gdb\
    && apt-get install -y sudo wget curl vim zsh

RUN chsh -s /bin/zsh

RUN cd /tmp \
    && git clone https://github.com/atcoder/ac-library.git

RUN pip3.8 install atcoder-tools

RUN mkdir -p /root/.atcodertools/template
RUN mkdir -p /root/atcoder-workspace


RUN curl -s -S https://gist.githubusercontent.com/gghatano/1aab64239be88181d0fc91069c6fe9b4/raw/625a707e7b0c38777e5b8e9984871481243a8597/template.cpp >> /root/.atcodertools/template/template.cpp
RUN curl -s -S https://gist.githubusercontent.com/gghatano/1aab64239be88181d0fc91069c6fe9b4/raw/625a707e7b0c38777e5b8e9984871481243a8597/zzz_algorithm.cpp >> /root/atcoder-workspace/algorighm.cpp
RUN sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

# ARG shell_rc="/root/.bashrc"
ARG shell_rc="/root/.zshrc"

RUN python -m pip install markupsafe==2.0.1
# agenlogin tessoku-book --workspace /workspaces/atcoder
RUN echo 'asub="atcoder-tools submit -f -u"'
# TODO コンパイルオプションを増やす or makefileにする
#RUN echo 'alias atest_sub="g++-12 -g -Wfatal-errors -Wall -Wextra -Wshadow -Wconversion -Wfloat-equal -ftrapv -fsanitize=address,undefined -fno-omit-frame-pointer -fno-sanitize-recover -std=gnu++20 -I /tmp/ac-library main.cpp; atcoder-tools test"' >> ${shell_rc}
# コンパイルオプションマシマシだと、ローカルでTLEになるが、Atcoder上でコンパイルすると成功するケースがあったため、提出用のコンパイルオプションを変更
RUN echo 'alias atest_sub="g++-12 -std=gnu++20 -O2 -Wall -Wextra -mtune=native -march=native -fconstexpr-depth=2147483647 -fconstexpr-loop-limit=2147483647 -fconstexpr-ops-limit=2147483647 -I/tmp/ac-library main.cpp; atcoder-tools test"' >> ${shell_rc}
RUN echo 'alias atest="g++-12 -g -Wfatal-errors -Wall -Wextra -Wshadow -Wconversion -Wfloat-equal -ftrapv -fsanitize=address,undefined -fno-omit-frame-pointer -fno-sanitize-recover -std=gnu++20 -I /tmp/ac-library main.cpp -D DEFINED_ONLY_IN_LOCAL; atcoder-tools test"' >> ${shell_rc}
RUN echo 'alias agen="atcoder-tools gen --without-login --workspace=/workspaces/atcoder/contest --template /workspaces/atcoder/my_template.cpp"' >> ${shell_rc}
RUN echo 'alias agenlogin="atcoder-tools gen --workspace /workspaces/atcoder/contest --template /workspaces/atcoder/my_template.cpp"' >> ${shell_rc}
RUN echo 'alias asub="atcoder-tools submit -u"' >> ${shell_rc}

# Rust
# curl --proto '=https' --tlsv1.2 https://sh.rustup.rs -sSf | sh

# 以下はGithub Action用
# Homebrewのインストール
# RUN /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
# RUN echo 'eval "$(/home/linuxbrew/.linuxbrew/bin/brew shellenv)"' >> ${shell_rc}
# RUN eval "$(/home/linuxbrew/.linuxbrew/bin/brew shellenv)"

# RUN brew install act
# RUN curl https://raw.githubusercontent.com/nektos/act/master/install.sh | sudo bash

CMD ["/bin/zsh"]
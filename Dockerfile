FROM python:3.8

RUN apt-get update \
    && apt-get -y install --no-install-recommends apt-utils dialog 2>&1 \
    && apt-get -y install git iproute2 procps lsb-release gdb\
    && apt-get install -y sudo wget curl vim

RUN cd /tmp \
    && git clone https://github.com/atcoder/ac-library.git

RUN pip3.8 install atcoder-tools

RUN mkdir -p /root/.atcodertools/template
RUN mkdir -p /root/atcoder-workspace


RUN curl -s -S https://gist.githubusercontent.com/gghatano/1aab64239be88181d0fc91069c6fe9b4/raw/625a707e7b0c38777e5b8e9984871481243a8597/template.cpp >> /root/.atcodertools/template/template.cpp
RUN curl -s -S https://gist.githubusercontent.com/gghatano/1aab64239be88181d0fc91069c6fe9b4/raw/625a707e7b0c38777e5b8e9984871481243a8597/zzz_algorithm.cpp >> /root/atcoder-workspace/algorighm.cpp

RUN python -m pip install markupsafe==2.0.1
# agenlogin tessoku-book --workspace /workspaces/atcoder
RUN echo 'asub="atcoder-tools submit -f -u"'
# TODO コンパイルオプションを増やす or makefileにする
#RUN echo 'alias atest_sub="g++-12 -g -Wfatal-errors -Wall -Wextra -Wshadow -Wconversion -Wfloat-equal -ftrapv -fsanitize=address,undefined -fno-omit-frame-pointer -fno-sanitize-recover -std=gnu++20 -I /tmp/ac-library main.cpp; atcoder-tools test"' >> /root/.bashrc
# コンパイルオプションマシマシだと、ローカルでTLEになるが、Atcoder上でコンパイルすると成功するケースがあったため、提出用のコンパイルオプションを変更
RUN echo 'alias atest_sub="g++-12 -std=gnu++20 -O2 -Wall -Wextra -mtune=native -march=native -fconstexpr-depth=2147483647 -fconstexpr-loop-limit=2147483647 -fconstexpr-ops-limit=2147483647 -I/tmp/ac-library main.cpp; atcoder-tools test"' >> /root/.bashrc
RUN echo 'alias atest="g++-12 -g -Wfatal-errors -Wall -Wextra -Wshadow -Wconversion -Wfloat-equal -ftrapv -fsanitize=address,undefined -fno-omit-frame-pointer -fno-sanitize-recover -std=gnu++20 -I /tmp/ac-library main.cpp -D DEFINED_ONLY_IN_LOCAL; atcoder-tools test"' >> /root/.bashrc
RUN echo 'alias agen="atcoder-tools gen --without-login --workspace=/workspaces/atcoder --template /workspaces/atcoder/my_template.cpp"' >> /root/.bashrc
RUN echo 'alias agenlogin="atcoder-tools gen --workspace /workspaces/atcoder --template /workspaces/atcoder/my_template.cpp"' >> /root/.bashrc
RUN echo 'alias asub="atcoder-tools submit -u"' >> /root/.bashrc

# 以下はGithub Action用
# Homebrewのインストール
RUN /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
RUN echo 'eval "$(/home/linuxbrew/.linuxbrew/bin/brew shellenv)"' >> /root/.bashrc
RUN eval "$(/home/linuxbrew/.linuxbrew/bin/brew shellenv)"

# RUN brew install act
# RUN curl https://raw.githubusercontent.com/nektos/act/master/install.sh | sudo bash

# RUN mkdir -p /etc/opt/test
# COPY test.sh /etc/opt/test/
# COPY test2.sh /etc/opt/test/

# RUN mkdir -p /etc/sudoers.d/
# RUN touch /etc/sudoers.d/devcontainer

# # RUN /workspaces/atcoder/test.sh /usr/local/bin/test.sh

# ARG USERNAME=devcontainer
# ARG USER_UID=1000
# ARG USER_GID=$USER_UID

# RUN groupadd --gid $USER_GID $USERNAME \
#     && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME \
#     && apt-get update \
#     && apt-get install -y sudo \
#     # && echo "$USERNAME ALL=(ALL) NOPASSWD: ALL, /workspaces/atcoder/test.sh" > /etc/sudoers.d/$USERNAME \
#     && echo "$USERNAME ALL=(ALL) NOPASSWD: /etc/opt/test/test*.sh" > /etc/sudoers.d/$USERNAME \
#     && chmod 0440 /etc/sudoers.d/$USERNAME

# USER $USERNAME

CMD ["/bin/bash"]
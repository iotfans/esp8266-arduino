#!/bin/bash

# 设置远程仓库的地址
remote_url=git@github.com
# 获取当前时间
cur_date="`Date +%Y-%m-%d-%H:%M:%S`" 

echo ====================================================
echo                GitBook自动deploy脚本
echo ====================================================
echo 

# 仓库账户名配置
read -p '请输入仓库账户名(默认为iotfans):' -a ACCOUNT
if [ -z $ACCOUNT]
    then
    ACCOUNT='iotfans'
fi

# 仓库repo配置
read -p '请输入仓库Repo名(默认为esp8266-arduino):' -a REPO
if [ -z $REPO]
    then
    REPO='esp8266-arduino'
fi

:<<!
# 仓库别名
read -p '请输入远程仓库别名(默认为origin):' -a NAME
if [ -z $NAME ]
    then
    NAME='origin'
fi

:<<!
# 分支名
read -p '请输入分支名(默认为master):' -a BRANCH
if [ -z $BRANCH ]
    then
    BRANCH='master'
fi
!

# commit内容设置
read -p '请输入commit内容(默认为当前时间戳):' -a COMMIT
if [ -z $COMMIT ]
    then
    COMMIT=$cur_date
fi


# 生成_book文件
cd ../gitbook-repo/esp8266-arduino-gitbook/
rm -rf _book
gitbook init
gitbook install
gitbook build
cd _book
cp -rf ./* ../../../esp8266-arduino/
cd ../../../esp8266-arduino/

:<<!
rm -rf .deploy_git/* | egrep .deploy_git/.git
if [ ! -d ".deploy_git/" ];then
 cp -R _book/ .deploy_git/
else
 cp -R _book/* .deploy_git/
fi
cd .deploy_git/
!




#git init
#git remote add origin $remote_url:$ACCOUNT/$REPO.git
#git checkout -b gh-pages

# 切换为gh-pages分支
git checkout gh-pages
git add -A
git commit -m $COMMIT
git push --delete origin gh-pages
git push -f origin gh-pages

echo 
echo ====================================================
echo                     自动deploy完毕
echo ====================================================

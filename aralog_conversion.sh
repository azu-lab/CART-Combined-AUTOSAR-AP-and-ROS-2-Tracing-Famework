#!/bin/bash
# AUTOSARトレースポイント一括生成スクリプト
set -e


# 1. クライアント・サーバのCSV生成
if [ -f input/client.txt ]; then
    python3 Python/extract_autosar_tracepoints_client.py input/client.txt
fi
if [ -f input/server.txt ]; then
    python3 Python/extract_autosar_tracepoints_server.py input/server.txt
fi

# 2. tracepointコード生成
if [ -f output/autosar_tracepoints_client.csv ]; then
    python3 Python/autosar_tracepoints_client_to_tracepoint_code.py output/autosar_tracepoints_client.csv output/output_client_tracepoints.txt
else
    echo "output/autosar_tracepoints_client.csv が見つからないためクライアントのtracepoint生成をスキップします。"
fi

if [ -f output/autosar_tracepoints_server.csv ]; then
    python3 Python/autosar_tracepoints_server_to_tracepoint_code.py output/autosar_tracepoints_server.csv output/output_server_tracepoints.txt
else
    echo "output/autosar_tracepoints_server.csv が見つからないためサーバのtracepoint生成をスキップします。"
fi

# 3. 初期化tracepointコード生成
if [ -f output/output_client_tracepoints.txt ]; then
    python3 Python/make_init_tracepoints_client.py output/output_init_tracepoints_client.txt
else
    touch output/output_init_tracepoints_client.txt
fi
if [ -f output/output_server_tracepoints.txt ]; then
    python3 Python/make_init_tracepoints_server.py output/output_init_tracepoints_server.txt
else
    touch output/output_init_tracepoints_server.txt
fi

# output_init_tracepoints.txtにoutput/output_init_tracepoints_server.txtとoutput/output_init_tracepoints_client.txtを結合
cat output/output_init_tracepoints_server.txt output/output_init_tracepoints_client.txt > output/output_init_tracepoints.txt

# 4. Cファイルへのtracepoint挿入補助（必要に応じて）
# wrap_tracepoint.py は存在する複数の出力ファイルを参照するため、
# 無ければ空ファイルを作成して呼び出し側でのエラーを防止する。
if [ ! -f output/output_client_tracepoints.txt ]; then
    touch output/output_client_tracepoints.txt
    echo "/* (自動生成) クライアントtracepointファイルが無かったため空ファイルを作成しました。 */" > output/output_client_tracepoints.txt
fi
if [ ! -f output/output_server_tracepoints.txt ]; then
    touch output/output_server_tracepoints.txt
    echo "/* (自動生成) サーバtracepointファイルが無かったため空ファイルを作成しました。 */" > output/output_server_tracepoints.txt
fi
if [ ! -f output/output_init_tracepoints.txt ]; then
    touch output/output_init_tracepoints.txt
    echo "/* (自動生成) 初期化tracepointファイルが無かったため空ファイルを作成しました。 */" > output/output_init_tracepoints.txt
fi

python3 Python/wrap_tracepoint.py output/output_client_tracepoints.txt output/output_server_tracepoints.txt output/output_init_tracepoints.txt

# 5. 出力ファイルの置換処理（ファイルがあれば実行）
if [ -f tracepoint_code/output_client_tracepoints_injected.c ]; then
    sed -i 's/unix_ns1/unix_ns2/g' tracepoint_code/output_client_tracepoints_injected.c
else
    echo "tracepoint_code/output_client_tracepoints_injected.c が無いため置換処理をスキップします。"
fi

if [ -f tracepoint_code/output_init_tracepoints_injected.c ]; then
    sed -i 's/j++;//g' tracepoint_code/output_init_tracepoints_injected.c
else
    echo "tracepoint_code/output_init_tracepoints_injected.c が無いため置換処理をスキップします。"
fi

# 6.
# 6. write_lttng コード生成: 必要な tracepoint_code/*.c が無ければ空ファイルを作成して呼び出す
mkdir -p tracepoint_code
for f in output_init_tracepoints_injected.c output_server_tracepoints_injected.c output_client_tracepoints_injected.c output_ROS2_tracepoints_injected.c; do
    if [ ! -f "tracepoint_code/$f" ]; then
        echo "/* (自動生成) $f が無いため空のプレースホルダを作成しました。 */" > "tracepoint_code/$f"
    fi
done

python3 Python/make_write_lttng.py C++/template.c C++/write_lttng.c tracepoint_code/output_init_tracepoints_injected.c tracepoint_code/output_server_tracepoints_injected.c tracepoint_code/output_client_tracepoints_injected.c tracepoint_code/output_ROS2_tracepoints_injected.c

# echo "全処理が完了しました。"

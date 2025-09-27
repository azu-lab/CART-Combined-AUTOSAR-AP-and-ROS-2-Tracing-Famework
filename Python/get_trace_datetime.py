import re
import os
from datetime import datetime

class TraceInfo:
    """
    LTTng/ros2_tracing のメタデータファイルを解析し、日時情報を保持するクラス。
    ファイルパスを渡してインスタンスを作成すると、year, month, day などの
    プロパティを通じてトレース開始日時の各要素にアクセスできます。

    使用例:
        trace_info = TraceInfo("/path/to/metadata")
        if trace_info.is_valid():
            print(f"年は {trace_info.year} 年です。")
    """
    def __init__(self, metadata_path: str):
        """
        コンストラクタ。メタデータファイルを解析して日時情報を初期化します。

        Args:
            metadata_path (str): メタデータファイルのパス。
        """
        self.metadata_path = metadata_path
        self._datetime_obj: datetime | None = None
        
        datetime_str = self._extract_datetime_string()

        if datetime_str:
            try:
                # タイムゾーン情報('+0900'など)を含めてdatetimeオブジェクトに変換
                # フォーマット例: "20250807T181458+0900"
                self._datetime_obj = datetime.strptime(datetime_str, "%Y%m%dT%H%M%S%z")
            except ValueError:
                print(f"エラー: 日時文字列の形式が正しくありません: {datetime_str}")


    def _extract_datetime_string(self) -> str | None:
        """
        メタデータファイルから trace_creation_datetime 文字列を抽出する内部メソッド。
        """
        pattern = re.compile(r'trace_creation_datetime\s*=\s*"([^"]+)"')

        if not os.path.exists(self.metadata_path):
            print(f"エラー: ファイルが見つかりません: {self.metadata_path}")
            return None
        
        try:
            with open(self.metadata_path, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()
                match = pattern.search(content)
                if match:
                    return match.group(1)
                else:
                    return None
        except Exception as e:
            print(f"ファイルの読み込み中にエラーが発生しました: {e}")
            return None

    @property
    def year(self) -> int | None:
        """年を返します。"""
        return self._datetime_obj.year if self._datetime_obj else None

    @property
    def month(self) -> int | None:
        """月を返します。"""
        return self._datetime_obj.month if self._datetime_obj else None

    @property
    def day(self) -> int | None:
        """日を返します。"""
        return self._datetime_obj.day if self._datetime_obj else None
    
    @property
    def hour(self) -> int | None:
        """時を返します。"""
        return self._datetime_obj.hour if self._datetime_obj else None

    @property
    def minute(self) -> int | None:
        """分を返します。"""
        return self._datetime_obj.minute if self._datetime_obj else None
        
    @property
    def second(self) -> int | None:
        """秒を返します。"""
        return self._datetime_obj.second if self._datetime_obj else None

    @property
    def tzinfo(self):
        """タイムゾーン情報を返します。"""
        return self._datetime_obj.tzinfo if self._datetime_obj else None

    @property
    def datetime(self) -> datetime | None:
        """
        解析されたPythonのdatetimeオブジェクト全体を返します。
        日時の比較や計算に便利です。
        """
        return self._datetime_obj

    def is_valid(self) -> bool:
        """日時情報が正常に読み込めたかどうかを返します。"""
        return self._datetime_obj is not None


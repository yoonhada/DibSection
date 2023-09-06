class CVector2
{
public:
	FLOAT x;
	FLOAT y;

	CVector2(FLOAT = 0, FLOAT = 0);
	~CVector2(){}

	CVector2 operator-(void) const;

	CVector2 operator+(const CVector2& vec) const;
	CVector2 operator-(const CVector2& vec) const;

	FLOAT operator*(const CVector2& vec) const;

	//CVector2 operator*(const Matrix2& m) const;
	FLOAT operator^(const CVector2& vec) const;

	CVector2& operator+=(const CVector2& vec);
	CVector2& operator-=(const CVector2& vec);

	CVector2 operator*(const FLOAT scalar) const;
	CVector2 operator/(const FLOAT scalar) const;

	CVector2& operator*=(const FLOAT scalar);
	CVector2& operator/=(const FLOAT scalar);

	void Normalize(void);
};
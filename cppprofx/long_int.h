#pragma once

class LONG_INT
{
private:
	size_t len_;
	int *container_;
	LONG_INT(const int *str, int size);
public:
	LONG_INT() : len_(1), container_(new int[len_]) { container_[0] = 0; }
	/*LONG_INT(const LONG_INT&);*/
	LONG_INT(const char *str);
	~LONG_INT();
	const LONG_INT operator*(const LONG_INT&) const;
	LONG_INT &operator*=(const LONG_INT&);
	LONG_INT &operator=(const LONG_INT&);
	LONG_INT &operator=(const char *str);
	friend std::ostream &operator<<(std::ostream &os, const LONG_INT &thisObject);
};

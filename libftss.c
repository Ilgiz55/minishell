#include "minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*stng;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	stng = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!(stng))
		return (NULL);
	ft_memcpy(stng, s1, len1);
	ft_memcpy(&stng[len1], s2, len2);
	stng[len1 + len2] = '\0';
	return (stng);
}

char	*ft_strdup(const char *s1)
{
	int		cou;
	char	*string;

	cou = 0;
	while (s1[cou])
		cou++;
	string = (char *)malloc(sizeof(*s1) * (cou + 1));
	if (string == NULL)
		return (NULL);
	string[cou] = '\0';
	while (cou--)
		string[cou] = s1[cou];
	return (string);
}

char	*ft_substr(char const *s, unsigned int start, size_t	len)
{
	size_t	leng;
	char	*stng;

	if (!s || (start >= ft_strlen(s) || (len <= 0)))
		return (ft_strdup(""));
	leng = ft_strlen(&s[start]);
	if (len > leng)
	{
		stng = (char *)malloc(sizeof(*s) * (leng));
		if (!stng)
			return (NULL);
		ft_memmove(stng, &s[start], leng);
		stng[len] = '\0';
	}
	else
	{
		stng = malloc(sizeof(*s) * (len + 1));
		if (!stng)
			return (NULL);
		ft_memmove(stng, &s[start], len);
		stng[len] = '\0';
	}
	return (stng);
}

int	ft_isalnum(int c)
{
	if ((c > 47 && c < 58) || (c > 64 && c < 91) || (c > 96 && c < 123))
		return (1);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	else if (!s || s == 0)
		return (0);
	while (s && s[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t	n)
{
	unsigned char	*fis;
	unsigned char	*sec;
	size_t			i;

	i = 0;
	fis = (unsigned char *)s1;
	sec = (unsigned char *)s2;
	while ((fis[i] == sec[i]) && n > i && fis[i])
		i++;
	if (n == i)
		return (0);
	return (fis[i] - sec[i]);
}

int	size(int num)
{
	int	i;

	i = 0;
	if (num < 0)
	{
		num = num * -1;
		i++;
	}
	if (num == 0)
		return (1);
	while (num)
	{
		num = num / 10;
		i++;
	}
	return (i);
}

char	*vnos(char *rev, int n, int i)
{
	if (n < 0)
	{
		rev[0] = '-';
		n = n * -1;
	}
	rev[i] = '\0';
	if (n == 0)
		rev[0] = '0';
	while (n != 0)
	{
		if (n < 0)
			rev[0] = '-';
		i--;
		rev[i] = (n % 10) + '0';
		n = n / 10;
	}
	return (rev);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*rev;

	i = size(n);
	rev = (char *)malloc(sizeof(char) * (i + 1));
	if (!rev)
		return (NULL);
	if (n == -2147483648)
	{
		ft_strlcpy(rev, "-2147483648", 12);
		return (rev);
	}
	vnos(rev, n, i);
	return (rev);
}

void	*ft_memcpy(void *dst, const void *src, size_t	n)
{
	size_t	i;

	i = 0;
	while ((n > i) && (dst || src))
	{
		((unsigned char *)dst)[i] = ((unsigned const char *)src)[i];
		i++;
	}
	return (dst);
}

int	ft_memcmp(const void *s1, const void *s2, size_t	n)
{
	unsigned char	*fir;
	unsigned char	*sec;

	fir = (unsigned char *)s1;
	sec = (unsigned char *)s2;
	if ((fir == sec) || n == 0)
		return (0);
	while (n)
	{
		if (*fir != *sec)
			return (*fir - *sec);
		fir++;
		sec++;
		n--;
	}
	return (0);
}

void	makeclean(char **s, int i)
{
	while (i > 0)
	{
		free(s[i]);
		i--;
	}
	free(s);
}

void	line(char **stolb, int nw, const char *s, char cut)
{
	int	coul;
	int	i;

	i = 0;
	while ((s) && (nw > i))
	{
		while ((*s == cut) && (*s != '\0'))
			s++;
		coul = 0;
		while (*s && (*s != cut))
		{
			coul++;
			s++;
		}
		stolb[i] = (char *) malloc(sizeof(char) * (coul + 1));
		if (!*stolb)
			makeclean(stolb, i);
		ft_strlcpy(stolb[i], s - coul, coul + 1);
		i++;
	}
	stolb[nw] = NULL;
}

int	couword(char const *str, char cut)
{
	int	cou;

	cou = 0;
	if (!(str[0]))
		return (cou);
	while (*str)
	{
		while (ft_strchr(&cut, *str) && *str)
			str++;
		while (*str && (*str != cut))
			str++;
		cou++;
	}
	if (*--str == cut)
		return (cou - 1);
	return (cou);
}

char	**ft_split(char const *s, char c)
{
	int		nw;
	char	**stolb;

	if (s == NULL)
		return (NULL);
	nw = couword(s, c);
	stolb = (char **) malloc(sizeof(char *) * (nw + 1));
	if (!stolb)
		return (NULL);
	line(stolb, nw, s, c);
	return (stolb);
}

void	*ft_memmove(void *dst, const void *src, size_t	len)
{
	size_t				i;
	unsigned char		*to;
	const unsigned char	*from;

	i = len;
	to = (unsigned char *)dst;
	from = (const unsigned char *)src;
	if (!src && !dst)
		return (NULL);
	if (to > from)
		while (len--)
			to[len] = from[len];
	else if (to <= from)
		while (0 < i--)
			to[len - i - 1] = from[len - i - 1];
	return (dst);
}

char	*ft_strchr(const char *s, int c)
{
	int		clo;
	char	*fis;

	clo = 0;
	fis = (char *)s;
	while (fis[clo])
	{
		if (fis[clo] == (const char)c)
			return (fis + clo);
		clo++;
	}
	if (c == '\0')
		return (&fis[clo]);
	return (NULL);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t	dstsize)
{
	size_t	i;
	size_t	num;

	num = 0;
	i = 0;
	if (!src || !dst)
		return (0);
	num = (ft_strlen(src));
	if (dstsize == 0)
		return (num);
	while ((src[i]) && (dstsize-- > 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (num);
}

int	ft_isalpha(int c)
{
	if ((c > 64 && c < 91) || (c > 96 && c < 123))
		return (1);
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t	len)
{
	char	*s1;
	char	*s2;
	size_t	len2;
	size_t	i;
	size_t	exi;

	i = 0;
	s1 = (char *)haystack;
	s2 = (char *)needle;
	len2 = (ft_strlen(s2));
	if (!s2 || !len2)
		return (s1);
	while (s1[i] && (i <= (len - len2)) && (len >= len2))
	{
		exi = 0;
		while (s1[i + exi] == s2[exi])
		{
			if (len2 - 1 == exi)
				return (s1 + i);
			exi++;
		}
		i = i + 1;
	}
	return (0);
}

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	return (0);
}

char	*ft_strrchr(const char *s, int c)
{
	int		clo;
	char	*fis;

	clo = ft_strlen(s) - 1;
	fis = (char *)s;
	if (c == '\0')
		return (&fis[clo + 1]);
	while (clo >= 0)
	{
		if (fis[clo] == (char)c)
			return (fis + clo);
		clo--;
	}
	return (NULL);
}

void	*ft_calloc(size_t	count, size_t	size)
{
	char	*p;

	p = malloc(count * size);
	if (!p)
		return (NULL);
	ft_memset(p, 0, count * size);
	return (p);
}

void	*ft_memset(void *b, int c, size_t	len)
{
	unsigned char	all;
	unsigned char	*num;

	all = (unsigned char)c;
	num = (unsigned char *)b;
	while (len-- > 0)
		num[len] = all;
	return (b);
}

int	ft_atoi(const char *str)
{
	long	bet;
	int		cou;

	cou = 1;
	bet = 0;
	while (str && ((*str == '\f') | (*str == '\t') | (*str == '\v')
	| (*str == '\r') | (*str == '\n') | (*str == ' ')))
		str++;
	if ((*str == '-') || (*str == '+'))
		if (*str++ == '-')
			cou = -1;
		while (str && ((*str >= '0') && (*str <= '9')))
		{
			if ((bet > 2147483647) && (cou == 1))
				return (-1);
			else if ((bet > 2147483647) && (cou == -1))
				return (0);
			bet = bet * 10 + (*str - '0');
			str++;
		}
		return (cou * bet);
}

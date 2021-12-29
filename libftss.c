#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t	n)
{
	unsigned char	*fis;
	unsigned char	*sec;
	size_t			i;

	i = 0;
	fis = (unsigned char *)s1;
	sec = (unsigned char *)s2;
	if (!sec && ! fis)
		return (0);
	if (!sec)
		return(fis[i]);
	if (!fis)
		return (- sec[i]);
	while (sec && fis && sec[i] && fis[i] && (fis[i] == sec[i]) && n > i)
		i++;
	if (n == i)
		return (0);
	return (fis[i] - sec[i]);
}

void	*ft_memcpy(void *dst, const void *src, size_t	n)
{
	size_t	i;

	i = 0;
	while (dst && src && (n > i) && (dst || src))
	{
		((unsigned char *)dst)[i] = ((unsigned const char *)src)[i];
		i++;
	}
	return (dst);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s || s == NULL)
		return (0);
	while (*s && s && s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*stng;
	size_t	len1;
	size_t	len2;

//	if (!s1 || !s2)
//		return (NULL);
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

int	ft_isalpha(int c)
{
	if ((c > 64 && c < 91) || (c > 96 && c < 123))
		return (1);
	return (0);
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

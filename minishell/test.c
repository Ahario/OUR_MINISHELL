/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_example.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seushin <seushin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 20:59:43 by seushin           #+#    #+#             */
/*   Updated: 2021/05/28 20:20:03 by seushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** refer:
** - https://www.gnu.org/software/termutils/manual/termcap-1.3/html_mono/termcap.html
** - https://man7.org/linux/man-pages/man3/termios.3.html
** - https://hyeonski.tistory.com/6?category=471028
*/

// 컴파일시 -ltermcap 옵션 추가
#include <termcap.h> // tgetent, tgetstr, tputs
#include <termios.h> // struct termios, tc~로 시작하는 것들
#include <stdlib.h> // getenv
#include <unistd.h>

# define KEY_LEFT 4479771
# define KEY_RIGHT 4414235
# define KEY_UP 4283163
# define KEY_DOWN 4348699
# define KEY_BACKSPACE 127
# define CTRL_D 4

struct termios		backup;

int		ft_isprint(int c)
{
	return (c >= 32 && c < 127);
}

int		ft_putchar(int c)
{
	write(STDOUT_FILENO, &c, 1);
	return (EXIT_SUCCESS);
}

int		init(void)
{
	struct termios	term;

	/*
	** int	tcgetattr(int fd, struct termios *term);
	** 터미널에 연결된 fd의 속성들을 term으로 가져온다.
	** 원래 설정으로 돌아갈 필요가 있다면 백업을 하나 만들어두자.
	*/
	tcgetattr(STDIN_FILENO, &backup);
	tcgetattr(STDIN_FILENO, &term);
	/*
	** 터미널 속성을 변경한다.
	** 1. 플래그 비트(캐노니컬모드, 입력된 글자를 출력하는 모드)를 끈다.
	** 2. MIN, TIME
	**   read 함수가 값을 읽는 방식을 설정한다.
	**   TIME은 read가 입력을 기다리는 시간을 설정하고
	**   MIN은 한번에 읽어들일 최소 바이트를 의미하는 듯하다.
	**   즉 1바이트 이상의 입력을 받으면 read는 즉시 값을 반환하고 종료한다.
	*/
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	/*
	** 변경한 속성을 적용한다.
	** TCSANOW - 변경사항을 즉시 적용
	** TCSAFLUSH - fd의 버퍼가 비워진 뒤 적용
	*/
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (EXIT_SUCCESS);
}

void	reset_term(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &backup);
}

int		main(void)
{
	int				n;
	int				c; // buffer, 특수키는 ascii 값(1바이트)으로 담을 수 없다.
	int				x; // 커서 위치
	int				len; // 문자열 길이

	/*
	** 환경변수 값을 이용해 터미널 정보를 가져와 termcap.h의 전역변수에 저장.
	** termcap 라이브러리를 사용하기 위해 가장 먼저 호출한다.
	** term database에 접근하지 못한다면 -1을 반환하고,
	** 접근하였지만 일치하는 터미널이 없다면? 0을 반환한다.
	*/
	if ((n = tgetent(NULL, getenv("TERM"))) < 1)
		return (EXIT_FAILURE);

	// 아래부터는 minishell 루프 안에서 인풋을 받는 부분이다.
	// 문자열을 저장하기 위해서는 별도의 코드가 필요하다.
	if (init())
		return (EXIT_FAILURE);
	c = x = len = 0;
	while ((n = read(STDIN_FILENO, &c, sizeof(c))) > 0)
	{
		if (c == KEY_LEFT && x > 0)
		{
			tputs(tgetstr("le", NULL), 1, ft_putchar); // cursor를 왼쪽으로 한 칸 이동
			x--;
		}
		else if (c == KEY_RIGHT && x < len)
		{
			tputs(tgetstr("nd", NULL), 1, ft_putchar); // cursor를 오른쪽으로 한 칸 이동
			x++;
		}
		else if (c == KEY_BACKSPACE && x > 0)
		{
			tputs(tgetstr("le", NULL), 1, ft_putchar); // cursor를 왼쪽으로 한 칸 이동
			tputs(tgetstr("dm", NULL), 1, ft_putchar); // delete 모드 진입
			tputs(tgetstr("dc", NULL), 1, ft_putchar); // delete character
			tputs(tgetstr("ed", NULL), 1, ft_putchar); // delete 모드 종료
			x--;
			len--;
		}
		else if (ft_isprint(c) || c == '\n')
		{
			tputs(tgetstr("im", NULL), 1, ft_putchar); // insert모드 진입
			tputs(tgetstr("ic", NULL), 1, ft_putchar); // insert char
			ft_putchar(c);
			tputs(tgetstr("ip", NULL), 1, ft_putchar); // insert pad
			tputs(tgetstr("ei", NULL), 1, ft_putchar); // insert모드 종료
			x++;
			len++;
			if (c == '\n')
				x = len = 0;
		}
		else if (c == CTRL_D) // EOF (c == CTRL_D && len == 0)
			break ;
		c = 0;
	}
	reset_term();
	return (EXIT_SUCCESS);
}

-lreadline
-L/home/linuxbrew/.linuxbrew/Cellar/readline/8.1.2/lib
-I/home/linuxbrew/.linuxbrew/Cellar/readline/8.1.2/include 

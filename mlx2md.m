% install mtlbx from addons directly
% - eval(webread('https://git.io/JYcyl'))

% convert
livescript2markdown('README.mlx', 'README.md', 'AddMention', false);
livescript2markdown('TEST.mlx', 'TEST.md', 'AddMention', false);
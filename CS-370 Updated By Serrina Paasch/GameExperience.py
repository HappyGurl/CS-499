import numpy as np

class GameExperience:
    """
    This class stores episodes using prioritized experience replay, where episodes with higher
    priority (larger TD errors) are more likely to be replayed.
    """
    
    def __init__(self, model, max_memory=100, discount=0.95, alpha=0.6, beta=0.4, epsilon=1e-6):
        """
        Args:
            model: Neural network model for predictions.
            max_memory: Maximum number of episodes to store in memory.
            discount: Discount factor for future rewards.
            alpha: Prioritization factor; controls how much prioritization is used (0 = uniform, 1 = full prioritization).
            beta: Importance sampling weight factor for bias correction.
            epsilon: Small constant to avoid zero priorities.
        """
        self.model = model
        self.max_memory = max_memory
        self.discount = discount
        self.alpha = alpha
        self.beta = beta
        self.epsilon = epsilon
        self.memory = []  # Stores experiences
        self.priorities = []  # Stores priorities for prioritized replay
        self.num_actions = model.output_shape[-1]
    
    def remember(self, episode, td_error):
        """
        Stores an episode in memory with its associated TD error, which determines its priority.

        Args:
            episode: A tuple containing (envstate, action, reward, envstate_next, game_over).
            td_error: Temporal Difference error used to assign a priority to the experience.
        """
        priority = (abs(td_error) + self.epsilon) ** self.alpha  # Calculate priority
        self.memory.append(episode)
        self.priorities.append(priority)

        # Ensure memory does not exceed max_memory
        if len(self.memory) > self.max_memory:
            del self.memory[0]
            del self.priorities[0]
    
    def predict(self, envstate):
        """
        Predicts the Q-values for a given environment state using the model.

        Args:
            envstate: The current environment state.

        Returns:
            The predicted Q-values for all possible actions.
        """
        return self.model.predict(envstate)[0]

    def get_td_error(self, envstate, action, reward, envstate_next, game_over):
        """
        Calculates the Temporal Difference (TD) error for a given experience.

        Args:
            envstate: Current environment state.
            action: Action taken.
            reward: Reward received.
            envstate_next: Next environment state.
            game_over: Whether the episode has ended.

        Returns:
            The TD error for the given experience.
        """
        target = self.predict(envstate)
        Q_sa = np.max(self.predict(envstate_next))
        if game_over:
            td_error = reward - target[action]
        else:
            td_error = reward + self.discount * Q_sa - target[action]
        return td_error

    def get_data(self, data_size=10):
        """
        Returns a batch of data from memory, sampled based on their priorities.

        Args:
            data_size: Number of samples to return.

        Returns:
            inputs: Input states for training.
            targets: Target Q-values for training.
        """
        mem_size = len(self.memory)
        data_size = min(mem_size, data_size)

        # Normalize priorities to create a probability distribution
        probabilities = np.array(self.priorities) / np.sum(self.priorities)

        # Sample indices based on priority probabilities
        indices = np.random.choice(range(mem_size), size=data_size, p=probabilities)

        # Compute importance-sampling weights
        weights = (mem_size * probabilities[indices]) ** (-self.beta)
        weights /= weights.max()  # Normalize the weights

        env_size = self.memory[0][0].shape[1]  # Get environment state size from first memory element
        inputs = np.zeros((data_size, env_size))
        targets = np.zeros((data_size, self.num_actions))

        for i, idx in enumerate(indices):
            envstate, action, reward, envstate_next, game_over = self.memory[idx]
            inputs[i] = envstate

            # Predict the Q-values for the current state
            targets[i] = self.predict(envstate)
            Q_sa = np.max(self.predict(envstate_next))

            # Update the target Q-value for the action taken
            if game_over:
                targets[i, action] = reward
            else:
                targets[i, action] = reward + self.discount * Q_sa

            # Adjust target using importance-sampling weight
            targets[i, action] *= weights[i]

        return inputs, targets

    def update_priorities(self, indices, td_errors):
        """
        Updates the priorities of the experiences based on new TD errors.

        Args:
            indices: List of indices corresponding to the experiences being updated.
            td_errors: New TD errors for the experiences.
        """
        for i, idx in enumerate(indices):
            self.priorities[idx] = (abs(td_errors[i]) + self.epsilon) ** self.alpha

